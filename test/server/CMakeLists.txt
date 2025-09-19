cmake_minimum_required(VERSION 3.0)
project(test)

# #设置全局的C++标准
set(CMAKE_CXX_STANDARD 14)  # c14
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)   # Debug 调试用

# 设置可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH /bin)

set(LIBS
    /usr/lib/x86_64-linux-gnu/libprotobuf.a  # 静态链接protobuf
    /usr/lib/x86_64-linux-gnu/libpthread.a  # 静态链接pthread
    /usr/lib/x86_64-linux-gnu/libzookeeper_mt.a  # 静态链接zookeeper_mt
    /usr/local/lib/libmuduo_net.a  # 静态链接muduo_net
    /usr/local/lib/libmuduo_base.a  # 静态链接muduo_base
    /usr/local/lib/libspdlog.a  # 静态链接spdlog
)

find_package(yaml-cpp REQUIRED)

# 设置头文件
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/include/net
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/include/registry
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/include/rpc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/include/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/include/load_balance
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/proto
    /usr/local/include/muduo/net
    /usr/local/include/muduo/base
)

link_directories(${PROJECT_SOURCE_DIR}/../lib)  # 链接库文件目录

# 链接protobuf
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../proto/*.cc)

add_executable(server ${SRC_FILES} ${PROTO_FILES})

# 链接
target_link_libraries(server rpc yaml-cpp ${LIBS})

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../proto)

target_compile_options(server PRIVATE -std=c++11 -Wall)

set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)