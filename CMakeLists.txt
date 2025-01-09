cmake_minimum_required(VERSION 3.22)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

project(MyProj VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

set(BASE_DEPLOY_DIR /usr/local)

set(BINARY_DEPLOY_DIR ${BASE_DEPLOY_DIR}/bin)
set(LIBRARY_DEPLOY_DIR ${BASE_DEPLOY_DIR}/lib)

add_subdirectory(common)
add_subdirectory(prog1)
#add_subdirectory(prog2)
