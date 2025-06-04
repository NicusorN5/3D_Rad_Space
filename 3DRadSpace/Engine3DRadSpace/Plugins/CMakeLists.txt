cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Plugins")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace_Plugins STATIC ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace_Plugins PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_Plugins PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace_Plugins PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace_Plugins PRIVATE "/Zi")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace STREQUAL "Debug")
		target_compile_options(3DRadSpace_Plugins PRIVATE "/fsanitize=address")
	endif()

	#MSVC doesn't define NDEBUG itself, dirty hack.
	if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		target_compile_definitions(3DRadSpace_Plugins PUBLIC NDEBUG 1)
	endif()
endif()

target_link_libraries(3DRadSpace_Plugins PRIVATE 3DRadSpace_Objects)
target_link_libraries(3DRadSpace_Plugins PRIVATE 3DRadSpace_Native)
target_include_directories(3DRadSpace_Plugins PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)