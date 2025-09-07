cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Content.Assets")

add_library(3DRadSpace.Content.Assets STATIC 
	"NullAsset.cpp"
	"SkyboxAsset.cpp"
	"TextureAsset.cpp"
 "FontAsset.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Content.Assets PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Content.Assets PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Content.Assets PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Content.Assets PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Content.Assets PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace.Content.Assets STREQUAL "Debug")
		target_compile_options(3DRadSpace.Content.Assets PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Content.Assets PRIVATE [[E3DRSP_CONTENT_ASSETS_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace.Content.Assets PRIVATE USING_DX11=1 _WINDLL=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace.Content.Assets PRIVATE USING_VULKAN=1)
endif()

#
#Dependencies 
#

target_link_libraries(3DRadSpace.Content.Assets PRIVATE 3DRadSpace_Core)
target_link_libraries(3DRadSpace.Content.Assets PRIVATE 3DRadSpace_Math)
target_link_libraries(3DRadSpace.Content.Assets PRIVATE 3DRadSpace_Audio)
target_link_libraries(3DRadSpace.Content.Assets PRIVATE 3DRadSpace_Games)
target_link_libraries(3DRadSpace.Content.Assets PRIVATE 3DRadSpace_Graphics)
target_include_directories(3DRadSpace.Content.Assets PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)