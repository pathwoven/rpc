# cmake_minimum_required(VERSION 3.0)
# project(rpc)

# #设置全局的C++标准
# set(CMAKE_CXX_STANDARD 14)  # c14
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_BUILD_TYPE Debug)   # Debug 调试用

# 查找spdlog包
if(NOT TARGET spdlog)          # 如果当前 CMake 工程中未定义名为 `spdlog` 的目标
    find_package(spdlog REQUIRED)  # 从系统路径查找并加载已安装的 spdlog 库
endif()
#查找protobuf包
set(Protobuf_LIBRARIES /usr/lib/x86_64-linux-gnu/libprotobuf.so)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

#设置链接库
# set(LIBS
#     protobuf
#     pthread
#     zookeeper_mt
#     muduo_net
#     muduo_base
#     spdlog
# )
set(LIBS
    /usr/lib/x86_64-linux-gnu/libprotobuf.a  # 静态链接protobuf
    /usr/lib/x86_64-linux-gnu/libpthread.a  # 静态链接pthread
    /usr/lib/x86_64-linux-gnu/libzookeeper_mt.a  # 静态链接zookeeper_mt
    /usr/local/lib/libmuduo_net.a  # 静态链接muduo_net
    /usr/local/lib/libmuduo_base.a  # 静态链接muduo_base
    /usr/local/lib/libspdlog.a  # 静态链接spdlog
)


# 指定库的生成路径
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)  # 动态库路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) # 静态库路径

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
aux_source_directory(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto)

# 创建库
add_library(rpc STATIC ${SRC_FILES} ${PROTO_FILES})

target_include_directories(rpc PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/net
    ${CMAKE_CURRENT_SOURCE_DIR}/include/registry
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rpc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/include/load_balance
    ${CMAKE_CURRENT_SOURCE_DIR}/proto
)

# 静态链接库
target_link_libraries(rpc PUBLIC -static ${LIBS})

target_compile_options(rpc PRIVATE -std=c++11 -Wall)

