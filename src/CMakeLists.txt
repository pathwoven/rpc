file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

# 创建动态库
add_library(rpc SHARED ${SRC_FILES})

target_include_directories(rpc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(rpc PRIVATE -std=c++11 -Wall)