file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../proto/*.cc)

link_libraries(rpc)
add_executable(client ${SRC_FILES} ${PROTO_FILES})

# 链接
# target_link_libraries(client ${PROJECT_SOURCE_DIR}/../lib/librpc.a)

target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../proto)

target_compile_options(client PRIVATE -std=c++11 -Wall)

set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)