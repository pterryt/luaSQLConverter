cmake_minimum_required(VERSION 3.30)
project(Learn)

#add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
set(CMAKE_CXX_STANDARD 20)
set(MYSQL_CONN_DIR C:/Users/Terry/Library/mysql-conn-9.1.0-64)
include_directories(include)
include_directories(external/header_only)
include_directories(${MYSQL_CONN_DIR}/include)
include_directories(${MYSQL_CONN_DIR}/include/jdbc)
include_directories(${MYSQL_CONN_DIR}/include/jdbc/cppconn)
link_directories(${MYSQL_CONN_DIR}/lib64/vs14)

set(SOURCES
        src/main.cpp
        src/FileHandler.cpp
        src/ConfigurationManager.cpp
        src/DatabaseHandler.cpp
        )


add_executable(Learn ${SOURCES})

target_link_libraries(Learn mysqlcppconn)

file(GLOB BINARY_FILES "${CMAKE_SOURCE_DIR}/external/bin/*")
file(COPY ${BINARY_FILES}
        DESTINATION ${CMAKE_BINARY_DIR})