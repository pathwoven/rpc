file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../proto/generated/*.cc)

add_executable(client ${SRC_FILES} ${PROTO_FILES})

# 链接
target_link_libraries(client rpc ${PROJECT_SOURCE_DIR}/lib/)

target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../proto/generated)

target_compile_options(client PRIVATE -std=c++11 -Wall)

set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)