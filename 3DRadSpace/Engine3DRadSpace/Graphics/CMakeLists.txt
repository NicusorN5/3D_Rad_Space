cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Graphics")

add_library(3DRadSpace.Graphics SHARED 
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
	"ShaderDesc.cpp"
	"EffectManager.cpp"
	"ShaderVariable.cpp"
	"IShaderCompiler.cpp"
	"IShader.cpp"
	"IGPUResource.cpp"
	"IGPUBuffer.cpp"
	"IVertexBuffer.cpp"
	"IGraphicsDevice.cpp"
	"IDepthStencilBuffer.cpp"
	"IIndexBuffer.cpp"
	"IDepthStencilState.cpp"
	"IGraphicsCommandList.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Graphics PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Graphics PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Graphics PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Graphics PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Graphics PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Graphics PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Graphics PRIVATE [[E3DRSP_GRAPHICS_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace.Graphics PRIVATE _WINDLL=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace.Graphics PRIVATE 3DRadSpace.Core)
target_link_libraries(3DRadSpace.Graphics PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Graphics PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Graphics PRIVATE 3DRadSpace.Logging)
target_include_directories(3DRadSpace.Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#DirectXTK
find_package(directxtk CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Graphics PRIVATE Microsoft::DirectXTK)

#assimp
find_package(assimp CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Graphics PRIVATE assimp::assimp)

#FreeType
find_package(freetype CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Graphics PRIVATE Freetype::Freetype)