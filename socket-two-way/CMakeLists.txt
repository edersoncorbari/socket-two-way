set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network)

set(HEADERS_FILES
    server.hxx
    tcp.hxx
    tcpthread.hxx
    global.hxx
    )

set(SOURCES_FILES
    server.cxx
    tcp.cxx
    tcpthread.cxx
    )

add_library(${PROJECT_NAME} SHARED
    ${HEADERS_FILES}
    ${SOURCES_FILES}
    )

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Network
    )

