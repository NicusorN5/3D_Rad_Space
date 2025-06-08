cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Input")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace_Input STATIC ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace_Input PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_Input PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace_Input PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace_Input PRIVATE "/Zi")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace_Graphics STREQUAL "Debug")
		target_compile_options(3DRadSpace_Input PRIVATE "/fsanitize=address")
	endif()

	#MSVC doesn't define NDEBUG itself, dirty hack.
	if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		target_compile_definitions(3DRadSpace_Input PUBLIC NDEBUG 1)
	endif()
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace_Input PRIVATE USING_DX11=1 _WINDLL=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace_Input PRIVATE USING_VULKAN=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace_Input PRIVATE 3DRadSpace_Core)
target_include_directories(3DRadSpace_Input PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
