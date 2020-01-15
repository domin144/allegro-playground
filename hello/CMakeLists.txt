cmake_minimum_required(VERSION 3.2)

project(hello)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Allegro IMPORTED_TARGET allegro)

add_executable(
    hello
    hello.cpp)

target_link_libraries(
    hello
    PkgConfig::Allegro)
