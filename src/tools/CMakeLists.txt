add_executable(server server.cpp ${BACKWARD_ENABLE})

target_include_directories(server PUBLIC ../include)

target_link_libraries(server PRIVATE DATABASE_LIB)

add_backward(server)
