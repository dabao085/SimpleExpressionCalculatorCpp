cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(SimpleExpressionCalculator)

include_directories("${PROJECT_SOURCE_DIR}/src")

#link_directories("${PROJECT_SOURCE_DIR}/third_party/3rdlib")

aux_source_directory(./src SRCS)

set(CMAKE_CXX_FLAGS "-O0 -Werror") # 设置C++ 工程的 CXX_FLAGS

add_executable(calculator ${SRCS}) # 生成可执行文件，这里程序名即为功能名

target_link_libraries(calculator pthread) # 链接库