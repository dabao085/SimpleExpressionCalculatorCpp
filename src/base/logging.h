#ifndef BASE_LOGGING_H
#define BASE_LOGGING_H

// GLOG defines this based on the system but doesn't check if it's already
// been defined.  undef it first to avoid warnings.
#undef _XOPEN_SOURCE
// This is including a glog internal file.  We want this to expose the
// function to get the stack trace.
#include "glog/logging.h"

//#define NOTREACHED() CHECK(false)

// Define verbose logging levels.  Per-row logging is more verbose than per-file
// per-rpc logging which is more verbose than per-connection / per-query logging.
#define VLOG_CONNECTION VLOG(1)
#define VLOG_RPC VLOG(8)
#define VLOG_QUERY VLOG(1)
#define VLOG_FILE VLOG(2)
#define VLOG_ROW VLOG(10)
#define VLOG_PROGRESS VLOG(2)
#define VLOG_TRACE VLOG(10)
#define VLOG_DEBUG VLOG(7)
#define VLOG_NOTICE VLOG(3)
#define VLOG_CRITICAL VLOG(1)


#define VLOG_CONNECTION_IS_ON VLOG_IS_ON(1)
#define VLOG_RPC_IS_ON VLOG_IS_ON(8)
#define VLOG_QUERY_IS_ON VLOG_IS_ON(1)
#define VLOG_FILE_IS_ON VLOG_IS_ON(2)
#define VLOG_ROW_IS_ON VLOG_IS_ON(10)
#define VLOG_TRACE_IS_ON VLOG_IS_ON(10)
#define VLOG_DEBUG_IS_ON VLOG_IS_ON(7)
#define VLOG_NOTICE_IS_ON VLOG_IS_ON(3)
#define VLOG_CRITICAL_IS_ON VLOG_IS_ON(1)


/// Define a wrapper around DCHECK for strongly typed enums that print a useful error
/// message on failure.
#define DCHECK_ENUM_EQ(a, b)                                                 \
    DCHECK(a == b) << "[ " #a " = " << static_cast<int>(a) << " , " #b " = " \
                   << static_cast<int>(b) << " ]"

namespace base {

// glog doesn't allow multiple invocations of InitGoogleLogging. This method conditionally
// calls InitGoogleLogging only if it hasn't been called before.
bool InitGlogSafe(const char* basename, bool install_signal_handler = false);

// Like InitGlogSafe() but stripped down: no signal handlers are
// installed, regular logging is disabled, and log events of any severity
// will be written to stderr.
//
// These properties make it attractive for us in libraries.
void InitGlogSafeBasic(const char* arg);

// Shuts down the google logging library. Call before exit to ensure that log files are
// flushed. May only be called once.
void ShutdownGlogSafe();

// Helper function that checks for the number of logfiles in the log directory and
// removes the oldest ones given an upper bound of number of logfiles to keep.
void CheckAndRotateLogFiles(int max_log_files);

} // namespace base


#endif // BASE_LOGGING_H
