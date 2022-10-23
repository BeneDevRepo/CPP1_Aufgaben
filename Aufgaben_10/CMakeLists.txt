cmake_minimum_required(VERSION 3.0.0)
project(Aufgaben_3 VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE files "src/*.cpp")
add_executable(Aufgaben_7 main.cpp ${files})
# add_executable(Aufgaben_5_Zahlenraten Zahlenraten.cpp ${files})
# target_include_directories(Aufgaben_5 PUBLIC "src")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
