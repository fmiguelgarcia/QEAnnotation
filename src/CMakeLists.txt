# Requirements 
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package( Qt5Core REQUIRED)
set( CMAKE_AUTOMOC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON)

# Source
set( QEAnnotation_MAYOR_VERSION 0)
set( QEAnnotation_MINOR_VERSION 1)
set( QEAnnotation_BUILD_VERSION 0)
set( QEAnnotation_SRCS
	QEAnnotationItem.cpp QEAnnotationModel.cpp QEAnnotation.cpp)

# Link
add_library( QEAnnotation SHARED ${QEAnnotation_SRCS})
target_link_libraries( QEAnnotation Qt5::Core ${CONAN_LIBS}) 
set_target_properties( QEAnnotation
	PROPERTIES 
	VERSION ${QEAnnotation_MAYOR_VERSION}.${QEAnnotation_MINOR_VERSION}.${QEAnnotation_BUILD_VERSION}
	SOVERSION ${QEAnnotation_MAYOR_VERSION}
	CXX_STANDARD 11)
