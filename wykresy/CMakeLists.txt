cmake_minimum_required(VERSION 3.2)

project(wykresy)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Allegro IMPORTED_TARGET allegro)

add_executable(
    wykresy
    main.cpp)

target_link_libraries(
    wykresy
    PkgConfig::Allegro)
