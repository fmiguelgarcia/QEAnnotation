find_package( Qt5Core)
find_package( Qt5Test)
set( CMAKE_AUTOMOC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON)

set( QAnnotationTest_SRCS
	AnnotateClassOne.cpp
	QAnnotationTest.cpp)

add_executable( QAnnotationTest ${QAnnotationTest_SRCS})
target_link_libraries( QAnnotationTest QAnnotation Qt5::Core Qt5::Test)
set_property( TARGET QAnnotationTest PROPERTY CXX_STANDARD 11)
set_property( TARGET QAnnotationTest APPEND_STRING PROPERTY COMPILE_FLAGS "-Wall -std=c++11")

add_test( QAnnotationTest_ QAnnotationTest)
