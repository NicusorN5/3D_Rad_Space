cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Graphics")

add_library(3DRadSpace_Graphics SHARED 
	"Effect.cpp"
	"FlipMode.cpp"
	"Font.cpp"
	"IBlendState.cpp"
	"ITexture2D.cpp"
	"ModelMesh.cpp"
	"ModelMeshPart.cpp"
	"Model3D.cpp"
	"SpriteBatch.cpp"
	"Viewport.cpp"
	"NullShader.cpp"
 )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace_Graphics PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_Graphics PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace_Graphics PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace_Graphics PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace_Graphics PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace_Graphics STREQUAL "Debug")
		target_compile_options(3DRadSpace_Graphics PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace_Graphics PRIVATE [[E3DRSP_GRAPHICS_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace_Graphics PRIVATE USING_DX11=1 _WINDLL=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace_Graphics PRIVATE USING_VULKAN=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace_Graphics PRIVATE 3DRadSpace_Core)
target_link_libraries(3DRadSpace_Graphics PRIVATE 3DRadSpace_Reflection)
target_link_libraries(3DRadSpace_Graphics PRIVATE 3DRadSpace_Math)
target_include_directories(3DRadSpace_Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#DirectXTK
find_package(directxtk CONFIG REQUIRED)
target_link_libraries(3DRadSpace_Graphics PRIVATE Microsoft::DirectXTK)

#assimp
find_package(assimp CONFIG REQUIRED)
target_link_libraries(3DRadSpace_Graphics PRIVATE assimp::assimp)

#FreeType
find_package(freetype CONFIG REQUIRED)
target_link_libraries(3DRadSpace_Graphics PRIVATE Freetype::Freetype)