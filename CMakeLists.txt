cmake_minimum_required(VERSION 3.26)
project(gmeme C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

add_executable(${PROJECT_NAME} src/main.c
        src/gmeme-paintable.c
        src/gmeme-paintable.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::GTK4)