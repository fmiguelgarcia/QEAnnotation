include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package( Qt5Core)
find_package( Qt5Test)
set( CMAKE_AUTOMOC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON)

set( QAnnotationTest_SRCS
	AnnotateClassOne.cpp
	QAnnotationTest.cpp)

add_executable( QAnnotationTest ${QAnnotationTest_SRCS})
target_link_libraries( QAnnotationTest QEAnnotation Qt5::Core Qt5::Test)
set_target_properties( QAnnotationTest PROPERTIES CXX_STANDARD 11)

add_test( NAME QEAnnotationTest COMMAND  $<TARGET_FILE:QAnnotationTest>)
