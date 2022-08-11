cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(SimpleExpressionCalculator)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/base")
include_directories("${PROJECT_SOURCE_DIR}/third_party")

link_directories("${PROJECT_SOURCE_DIR}/third_party/3rdlib")

aux_source_directory(./src SRCS)
aux_source_directory(./src/base SRCS)

set(CMAKE_CXX_FLAGS "-O0 -Werror") # 设置C++ 工程的 CXX_FLAGS

add_executable(calculator ${SRCS}) # 生成可执行文件，这里程序名即为功能名

target_link_libraries(calculator
        pthread
        glog
        gflags
        pthread
        unwind) # 链接库