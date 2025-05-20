# cmake_minimum_required(VERSION 3.0)
# project(rpc)

# #设置全局的C++标准
# set(CMAKE_CXX_STANDARD 14)  # c14
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_BUILD_TYPE Debug)   # Debug 调试用

add_subdirectory(server)
add_subdirectory(client)