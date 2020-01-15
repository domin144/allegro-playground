cmake_minimum_required(VERSION 3.2)

project(pacman)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Allegro IMPORTED_TARGET allegro)

add_executable(
    pacman
    pacman.cpp)

target_link_libraries(
    pacman
    PkgConfig::Allegro)
