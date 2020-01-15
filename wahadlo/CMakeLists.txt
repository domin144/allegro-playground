cmake_minimum_required(VERSION 3.2)

project(wahadlo)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Allegro IMPORTED_TARGET allegro)

add_executable(
    wahadlo
    main.cpp)

target_link_libraries(
    wahadlo
    PkgConfig::Allegro)
