# cmake_minimum_required(VERSION 3.0)
# project(example)

# # #设置全局的C++标准
# set(CMAKE_CXX_STANDARD 14)  # c14
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_BUILD_TYPE Debug)   # Debug 调试用

# 设置可执行文件的输出目录
# set(EXECUTABLE_OUTPUT_PATH /bin)

# add_subdirectory(${CMAKE_SOURCE_DIR}/../src ${CMAKE_BINARY_DIR}/src)
add_subdirectory(server)
add_subdirectory(client)