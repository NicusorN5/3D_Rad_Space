cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Graphics")

add_library(3DRadSpace.Graphics SHARED 
	"Blend.hpp"
	"Blend.h"
	"BlendOperation.hpp"
	"BlendOperation.h"
	"BufferUsage.hpp"
	"BufferUsage.h"
	"ColorWriteEnable.hpp"
	"ColorWriteEnable.h"
	"ComparisonFunction.hpp"
	"ComparisonFunction.h"
	"DepthWriteMask.hpp"
	"DepthWriteMask.h"
	"Effect.hpp"
	"Effect.cpp"
	"Effect.h"
	"EffectManager.hpp"
	"EffectManager.cpp"
	"EffectManager.h"
	"FlipMode.hpp"
	"FlipMode.cpp"
	"FlipMode.h"
	"Font.hpp"
	"Font.cpp"
	"Font.h"
	"Glyph.hpp"
	"Glyph.h"
	"IBlendState.hpp"
	"IBlendState.cpp"
	"IBlendState.h"
	"IDepthStencilBuffer.hpp"
	"IDepthStencilBuffer.cpp"
	"IDepthStencilBuffer.h"
	"IDepthStencilState.hpp"
	"IDepthStencilState.cpp"
	"IDepthStencilState.h"
	"IGPUBuffer.hpp"
	"IGPUBuffer.cpp"
	"IGPUBuffer.h"
	"IGPUResource.hpp"
	"IGPUResource.cpp"
	"IGPUResource.h"
	"IGraphicsCommandList.hpp"
	"IGraphicsCommandList.cpp"
	"IGraphicsCommandList.h"
	"IGraphicsDevice.hpp"
	"IGraphicsDevice.cpp"
	"IGraphicsDevice.h"
	"IIndexBuffer.hpp"
	"IIndexBuffer.cpp"
	"IIndexBuffer.h"
	"IRasterizerState.hpp"
	"IRasterizerState.cpp"
	"IRasterizerState.h"
	"IRenderTarget.hpp"
	"IRenderTarget.cpp"
	"IRenderTarget.h"
	"ISamplerState.hpp"
	"ISamplerState.cpp"
	"ISamplerState.h"
	"IShader.hpp"
	"IShader.cpp"
	"IShader.h"
	"IShaderCompiler.hpp"
	"IShaderCompiler.cpp"
	"IShaderCompiler.h"
	"ITexture1D.hpp"
	"ITexture1D.cpp"
	"ITexture1D.h"
	"ITexture2D.hpp"
	"ITexture2D.cpp"
	"ITexture2D.h"
	"ITextureCube.hpp"
	"ITextureCube.h"
	"ITextureCube.cpp"
	"IVertexBuffer.hpp"
	"IVertexBuffer.cpp"
	"IVertexBuffer.h"
	"ModelMesh.hpp"
	"ModelMesh.cpp"
	"ModelMesh.h"
	"ModelMeshPart.hpp"
	"ModelMeshPart.cpp"
	"ModelMeshPart.h"
	"Model3D.hpp"
	"Model3D.cpp"
	"Model3D.h"
	"NullShader.hpp"
	"NullShader.cpp"
	"PixelFormat.hpp"
	"PixelFormat.h"
	"RasterizerCullMode.hpp"
	"RasterizerCullMode.h"
	"RasterizerFillMode.hpp"
	"RasterizerFillMode.h"
	"RenderTargetBlendState.hpp"
	"RenderTargetBlendState.h"
	"ShaderCompilationError.hpp"
	"ShaderCompilationResult.hpp"
	"ShaderCompilationResult.h"
	"ShaderDesc.hpp"
	"ShaderDesc.cpp"
	"ShaderDesc.h"
	"ShaderFeatureLevel.hpp"
	"ShaderFeatureLevel.h"
	"ShaderType.hpp"
	"ShaderType.h"
	"ShaderVariable.hpp"
	"ShaderVariable.cpp"
	"SpriteBatch.hpp"
	"SpriteBatch.cpp"
	"SpriteBatch.h"
	"StencilOperation.hpp"
	"StencilOperation.h"
	"TextureAddressMode.hpp"
	"TextureAddressMode.h"
	"TextureFilter.hpp"
	"TextureFilter.h"
	"VertexDeclarations.hpp"
	"VertexDeclarations.h"
	"VertexTopology.hpp"
	"VertexTopology.h"
	"Viewport.hpp"
	"Viewport.cpp"
	"Viewport.h"
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