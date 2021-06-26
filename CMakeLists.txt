cmake_minimum_required(VERSION 3.19)
project(webserver)

set(CMAKE_CXX_STANDARD 98)

include_directories(libft)
include_directories(config_parser_v.0.1/includes)

add_executable(webserver main.cpp RequestHeaders.cpp RequestHeaders.hpp ResponseHeaders.cpp ResponseHeaders.hpp methods.cpp methods.h utils.cpp utils.hpp)

#find_library(LIBFT ft libft)
#target_link_libraries(webserver LINK_PUBLIC ${LIBFT})

find_library(LIBCONFPAR confpar config_parser_v.0.1)
target_link_libraries(webserver LINK_PUBLIC ${LIBCONFPAR})
