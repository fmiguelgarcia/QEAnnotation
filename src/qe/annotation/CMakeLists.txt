# Requirements 
include( ${CMAKE_SOURCE_DIR}/tools/cmake/common.cmake)
set( QEAnnotation_MAYOR_VERSION 0)
set( QEAnnotation_MINOR_VERSION 1)
set( QEAnnotation_BUILD_VERSION 0)

# Source
set( QEAnnotation_SRCS
	Item.cpp Model.cpp Annotation.cpp)

# Link
add_library( QEAnnotation SHARED ${QEAnnotation_SRCS})
target_link_libraries( QEAnnotation Qt5::Core ${CONAN_LIBS}) 
set_target_properties( QEAnnotation
	PROPERTIES 
	VERSION ${QEAnnotation_MAYOR_VERSION}.${QEAnnotation_MINOR_VERSION}.${QEAnnotation_BUILD_VERSION}
	SOVERSION ${QEAnnotation_MAYOR_VERSION})
target_compile_features( QEAnnotation PUBLIC cxx_auto_type cxx_lambdas 
	cxx_noexcept)
