file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../proto/*.cc)

# 链接
# link_libraries(rpc)

add_executable(server ${SRC_FILES} ${PROTO_FILES})

# 链接
target_link_libraries(server rpc ${LIBS})
# 链接
#target_link_libraries(server ${PROJECT_SOURCE_DIR}/../lib/librpc.a)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../proto)
# message(STATUS "Server source files:  ${CMAKE_CURRENT_SOURCE_DIR}/../proto")

target_compile_options(server PRIVATE -std=c++11 -Wall)

set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)