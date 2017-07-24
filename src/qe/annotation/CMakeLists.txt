# Requirements 
include( ${CMAKE_SOURCE_DIR}/tools/cmake/common.cmake)
find_package( Boost REQUIRED COMPONENTS serialization)
set( QEAnnotation_MAYOR_VERSION 1)
set( QEAnnotation_MINOR_VERSION 0)
set( QEAnnotation_BUILD_VERSION 0)

# Source
set( QEAnnotation_SRCS
	Global.hpp
	Item.cpp
	ModelPrivate.cpp
	Model.cpp
	Annotation.cpp)
add_definitions( -DQEANNOTATION_LIB_BUILD)

# Link
add_library( QEAnnotation SHARED ${QEAnnotation_SRCS})
target_link_libraries( QEAnnotation 
	Qt5::Core 
	Boost::serialization
	${CONAN_LIBS}) 

set_target_properties( QEAnnotation
	PROPERTIES 
	VERSION ${QEAnnotation_MAYOR_VERSION}.${QEAnnotation_MINOR_VERSION}.${QEAnnotation_BUILD_VERSION}
	SOVERSION ${QEAnnotation_MAYOR_VERSION})

target_compile_features( QEAnnotation 
	PUBLIC cxx_auto_type cxx_lambdas cxx_noexcept)
