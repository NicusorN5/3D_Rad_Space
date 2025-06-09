cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Internal")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace_Internal STATIC ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET (3DRadSpace_Internal PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_Internal PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace_Internal PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace_Internal PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace_Internal PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace_Graphics STREQUAL "Debug")
		target_compile_options(3DRadSpace_Internal PRIVATE "/fsanitize=address")
	endif()
endif()

#
#Dependencies 
#
target_link_libraries((3DRadSpace_Internal PRIVATE 3DRadSpace_Reflection)
target_include_directories(3DRadSpace_Internal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
