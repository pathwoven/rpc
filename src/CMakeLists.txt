file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
aux_source_directory(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto/generated)
# 创建动态库
add_library(rpc SHARED ${SRC_FILES} ${PROTO_FILES})

target_include_directories(rpc PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/net
    ${CMAKE_CURRENT_SOURCE_DIR}/include/registry
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rpc
    ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/proto/generated
)

target_compile_options(rpc PRIVATE -std=c++11 -Wall)