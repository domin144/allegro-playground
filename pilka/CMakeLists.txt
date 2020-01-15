cmake_minimum_required(VERSION 3.2)

project(pilka)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Allegro IMPORTED_TARGET allegro)

add_executable(
    pilka
    main.cpp)

target_link_libraries(
    pilka
    PkgConfig::Allegro)
