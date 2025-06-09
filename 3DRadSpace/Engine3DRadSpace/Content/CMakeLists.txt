cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Content")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace_Content STATIC ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace_Content PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_Content PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace_Content PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace_Content PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace_Content PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace_Content STREQUAL "Debug")
		target_compile_options(3DRadSpace_Content PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace_Content PRIVATE [[E3DRSP_CONTENT_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace_Content PRIVATE USING_DX11=1 _WINDLL=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace_Content PRIVATE USING_VULKAN=1)
endif()

#
#Dependencies 
#

target_link_libraries(3DRadSpace_Content PRIVATE 3DRadSpace_Math)
target_link_libraries(3DRadSpace_Content PRIVATE 3DRadSpace_Games)
target_include_directories(3DRadSpace_Content PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#assimp
find_package(assimp CONFIG REQUIRED)
target_link_libraries(3DRadSpace_Content PRIVATE assimp::assimp)

#DirectXTK
find_package(directxtk CONFIG REQUIRED)
target_link_libraries(3DRadSpace_Content PRIVATE Microsoft::DirectXTK)

#FreeType
find_package(freetype CONFIG REQUIRED)
target_link_libraries(3DRadSpace_Content PRIVATE Freetype::Freetype)