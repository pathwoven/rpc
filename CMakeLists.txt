cmake_minimum_required(VERSION 3.0)
project(rpc)

#设置全局的C++标准
set(CMAKE_CXX_STANDARD 11)  # c11
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找spdlog包
if(NOT TARGET spdlog)          # 如果当前 CMake 工程中未定义名为 `spdlog` 的目标
    find_package(spdlog REQUIRED)  # 从系统路径查找并加载已安装的 spdlog 库
endif()
#查找protobuf包
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

#设置全局链接库
set(LIBS
    protobuf
    pthread
    zookeeper_mt
    muduo_net
    muduo_base
    spdlog
)

add_subdirectory(src)
add_subdirectory(example)
