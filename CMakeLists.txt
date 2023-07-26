cmake_minimum_required(VERSION 3.26)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project(gmeme C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(sqlite3 REQUIRED)

include(GResourcesCompile)
CompileGResources(${CMAKE_CURRENT_SOURCE_DIR}/data)

add_executable(${PROJECT_NAME} src/main.c
        src/gmeme-paintable.c
        src/gmeme-paintable.h
        src/gmeme-gui.c
        src/gmeme-gui.h
        src/gmeme-app-data.c
        src/gmeme-app-data.h
        ${GRESOURCE_C}
        src/gmeme-utils.c
        src/gmeme-utils.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::GTK4 sqlite3)