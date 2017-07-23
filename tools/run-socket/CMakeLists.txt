include_directories("${CMAKE_SOURCE_DIR}")

add_executable(run-socket runsocket.cxx)

target_link_libraries(run-socket socket-two-way)


