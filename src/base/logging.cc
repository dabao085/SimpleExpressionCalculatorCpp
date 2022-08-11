#include "base/logging.h"
#include <glob.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mutex>
#include <string>
#include <set>

namespace base {

DEFINE_string(log_filename, "",
              "Prefix of log filename - "
              "full path is <log_dir>/<log_filename>.[INFO|WARN|ERROR|FATAL]");

static bool logging_initialized = false;

static std::mutex logging_mutex;

void DeleteOldLogs(const std::string &path_pattern, int max_log_files) {
    // Ignore bad input or disable log rotation
    if (max_log_files <= 0)
        return;

    // Modification time has resolution of seconds, so if there are high frequency updates,
    // there may be multiple log files with the same mtime. This set keeps mtime,
    // filename pairs, which allows tracking multiple files with the same mtime. This set
    // is sorted by mtime first with mtime ties broken by comparison of the filenames. This
    // is a good fit for the log files, because the log files commonly have a prefix + a
    // timestamp. Sorting on the filename in this case is sorting from oldest to newest,
    // which matches the mtime sorting.
    typedef std::set<std::pair<time_t, std::string>> LogFileMap;

    LogFileMap log_file_mtime;
    glob_t result;
    int glob_ret = glob(path_pattern.c_str(), GLOB_TILDE, NULL, &result);
    if (glob_ret != 0) {
        if (glob_ret != GLOB_NOMATCH) {
            LOG(ERROR) << "glob failed in DeleteOldLogs on " << path_pattern << " with ret = " << glob_ret;
        }
        globfree(&result);
        return;
    }

    for (size_t i = 0; i < result.gl_pathc; ++i) {
        // Get the mtime for each match
        struct stat stat_val;
        if (stat(result.gl_pathv[i], &stat_val) != 0) {
            LOG(ERROR) << "Could not read last-modified-timestamp for log file " << result.gl_pathv[i]
                       << ", will not delete (error was: " << strerror(errno) << ")";
            continue;
        }
        // Add mtime, filename pair to the set
        //    discard_result(log_file_mtime.emplace(stat_val.st_mtime, result.gl_pathv[i]));
        log_file_mtime.emplace(stat_val.st_mtime, result.gl_pathv[i]);
    }
    globfree(&result);

    // Iterate over the set and remove oldest log files first when too many
    // log files exist
    if (log_file_mtime.size() <= (unsigned)max_log_files)
        return;
    int files_to_delete = log_file_mtime.size() - max_log_files;
    DCHECK_GT(files_to_delete, 0);
    for (LogFileMap::const_reference val : log_file_mtime) {
        if (unlink(val.second.c_str()) == 0) {
            LOG(INFO) << "Old log file deleted during log rotation: " << val.second;
        } else {
            LOG(ERROR) << "Failed to delete old log file: " << val.second << "(error was: " << strerror(errno) << ")";
        }
        if (--files_to_delete == 0)
            break;
    }
}

bool InitGlogSafe(const char *basename, bool install_signal_handler) {
    std::lock_guard<std::mutex> logging_lock(logging_mutex);

    if (logging_initialized) {
        return true;
    }

    if (!FLAGS_log_filename.empty()) {
        for (int severity = google::INFO; severity <= google::FATAL; ++severity) {
            google::SetLogSymlink(severity, FLAGS_log_filename.c_str());
        }
    }

    // This forces our logging to use /tmp rather than looking for a
    // temporary directory if none is specified. This is done so that we
    // can reliably construct the log file name without duplicating the
    // complex logic that glog uses to guess at a temporary dir.
    if (FLAGS_log_dir.empty()) {
        FLAGS_log_dir = "/tmp";
    }

    if (install_signal_handler) {
        google::InstallFailureSignalHandler();
    }

    // don't log to stderr
    FLAGS_stderrthreshold = google::FATAL + 1;
    // 0 means buffer INFO only
    FLAGS_logbuflevel = 0;
    // buffer log messages for at most this many seconds
    FLAGS_logbufsecs = 30;

    google::InitGoogleLogging(basename);
    // Needs to be done after InitGoogleLogging
    if (FLAGS_log_filename.empty()) {
        FLAGS_log_filename = google::ProgramInvocationShortName();
    }

    logging_initialized = true;

    return true;
}

void InitGlogSafeBasic(const char *arg) {
    std::lock_guard<std::mutex> logging_lock(logging_mutex);
    if (logging_initialized)
        return;

    google::InitGoogleLogging(arg);

    // This also disables file-based logging.
    google::LogToStderr();

    logging_initialized = true;
}

void ShutdownGlogSafe() {
    std::lock_guard<std::mutex> logging_lock(logging_mutex);
    if (!logging_initialized)
        return;
    google::ShutdownGoogleLogging();
    logging_initialized = false;
}

void CheckAndRotateLogFiles(int max_log_files) {
    // Ignore bad input or disable log rotation
    if (max_log_files <= 1)
        return;
    // Check log files for all severities
    for (int severity = 0; severity < google::NUM_SEVERITIES; ++severity) {
        // Build glob pattern for input
        // e.g. /tmp/impalad.*.INFO.*
        //    std::string fname = strings::Substitute("$0/$1.*.$2*", FLAGS_log_dir, FLAGS_log_filename,
        //                                       google::GetLogSeverityName(severity));
        std::string fname(FLAGS_log_dir);
        fname.append(1, '/').append(FLAGS_log_filename).append(".*.");
        fname.append(google::GetLogSeverityName(severity)).append(1, '*');

        DeleteOldLogs(fname, max_log_files);
    }
}

} // namespace base
