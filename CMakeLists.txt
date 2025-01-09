cmake_minimum_required(VERSION 3.22)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

project(MyProj VERSION ${PROJECT_VERSION})

add_subdirectory(common)
add_subdirectory(prog1)
add_subdirectory(prog2)
