cmake_minimum_required(VERSION 4.00)
project(calm C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_executable(calm 
	main.c 
	src/cJSON.c
)
target_compile_options(calm PRIVATE -Wall -Wextra)
target_include_directories(calm PRIVATE src)
find_package(CURL REQUIRED)
target_link_libraries(calm PRIVATE CURL::libcurl)

