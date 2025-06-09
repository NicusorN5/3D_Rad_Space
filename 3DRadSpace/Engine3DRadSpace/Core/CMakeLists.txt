cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Core")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace_Core STATIC ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace_Core PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_Core PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace_Core PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace_Core PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace_Core PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace STREQUAL "Debug")
		target_compile_options(3DRadSpace_Core PRIVATE "/fsanitize=address")
	endif()

	#Define library specific library export macro
	target_compile_definitions(3DRadSpace_Core PRIVATE [[E3DRSP_CORE_EXPORT=__declspec(dllexport)]])
endif()