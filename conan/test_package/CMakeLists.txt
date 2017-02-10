project(QAnnotationTest)
cmake_minimum_required(VERSION 3.0.0)
find_package( Qt5Core REQUIRED)

set( CMAKE_AUTOMOC ON)
set( CMAKE_AUTOUIC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable( packageTest main.cpp)
target_link_libraries( packageTest Qt5::Core ${CONAN_LIBS})

set_property( TARGET packageTest  PROPERTY CXX_STANDARD 11)
set_property( TARGET packageTest APPEND_STRING PROPERTY COMPILE_FLAGS "-Wall -std=c++11")
