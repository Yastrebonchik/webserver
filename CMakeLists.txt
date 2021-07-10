cmake_minimum_required(VERSION 3.19)
project(webserver)

set(CMAKE_CXX_STANDARD 98)

include_directories(config_parser_v.0.1/includes)
include_directories(includes)

add_executable(webserver srcs/main.cpp srcs/RequestHeaders.cpp includes/RequestHeaders.hpp
        srcs/ResponseHeaders.cpp includes/ResponseHeaders.hpp srcs/methods.cpp includes/methods.h srcs/utils.cpp
        includes/utils.hpp srcs/ConnectionClass.cpp includes/ConnectionClass.hpp srcs/ConnectionHandling.cpp
        includes/ConnectionHandling.h srcs/cgi.cpp includes/cgi.hpp)

find_library(LIBCONFPAR confpar config_parser_v.0.1)
target_link_libraries(webserver LINK_PUBLIC ${LIBCONFPAR})
