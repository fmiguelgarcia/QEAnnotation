# Requirements 
include( ${CMAKE_SOURCE_DIR}/tools/cmake/common.cmake)
find_package( Boost REQUIRED COMPONENTS serialization)

# Source
set( QEAnnotation_SRCS
	Global.hpp
	Item.cpp Item.hpp
	ModelPrivate.cpp ModelPrivate.hpp
	Model.cpp Model.hpp
	Annotation.cpp Annotation.hpp)
add_definitions( -DQEANNOTATION_LIB_BUILD)

# Link
add_library( QEAnnotation SHARED ${QEAnnotation_SRCS})
target_link_libraries( QEAnnotation 
	Qt5::Core  Boost::serialization
	${CONAN_LIBS}) 

set( QEAnnotation_VERSION 0.1.0)
set_target_properties( QEAnnotation
	PROPERTIES 
	VERSION ${QEAnnotation_VERSION}
	SOVERSION 0)

target_compile_features( QEAnnotation 
	PUBLIC cxx_auto_type cxx_lambdas cxx_noexcept)
