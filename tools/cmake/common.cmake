# Include conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Find common packages.
find_package( Qt5Core REQUIRED)

# Qt setup.
set( CMAKE_AUTOMOC ON)
set( CMAKE_AUTOUIC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable All Warnings
if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	add_definitions( -Wall)
	# On GCC 5 : https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dual_abi.html 
	add_definitions( -Wabi-tag)
endif()

# Include common directory
include_directories( ${CMAKE_SOURCE_DIR}/src/)

# C++ 11
#target_compile_features( <target> PUBLIC cxx_auto_type cxx_constexpr
#	cxx_decltype cxx_defaulted_funtions cxx_deleted_functions
#	cxx_generalized_initializers cxx_lambdas cxx_noexcept cxx_nullptr
#	cxx_range_for )

set_property( GLOBAL PROPERTY CXX_STANDARD 11)
