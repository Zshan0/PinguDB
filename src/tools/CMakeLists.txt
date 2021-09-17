add_executable(server server.cpp)

target_include_directories(server PUBLIC ../include)

target_link_libraries(server PRIVATE DATABASE_LIB)
