cmake_minimum_required(VERSION 3.1)

project(a-star)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_subdirectory(src)

# executable
add_executable(a-star example/main.cpp)

target_link_libraries(a-star sfml-graphics a_starLib)