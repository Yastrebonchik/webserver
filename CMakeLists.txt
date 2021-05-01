cmake_minimum_required(VERSION 3.19)
project(webserver)

set(CMAKE_CXX_STANDARD 98)

include_directories(libft)
add_executable(webserver main.cpp RequestHeaders.cpp RequestHeaders.hpp ResponseHeaders.cpp ResponseHeaders.hpp)

find_library(LIBFT ft libft)
target_link_libraries(webserver LINK_PUBLIC ${LIBFT})