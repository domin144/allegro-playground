cmake_minimum_required(VERSION 3.2)

project(koch)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Allegro IMPORTED_TARGET allegro)

add_executable(
    koch
    main.cpp)

target_link_libraries(
    koch
    PkgConfig::Allegro)
