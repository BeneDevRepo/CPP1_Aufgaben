cmake_minimum_required(VERSION 3.0.0)
project(Aufgaben_3 VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE files "src/*.cpp")
add_executable(Aufgaben_3 main.cpp ${files})
target_include_directories(Aufgaben_3 PUBLIC "src")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
