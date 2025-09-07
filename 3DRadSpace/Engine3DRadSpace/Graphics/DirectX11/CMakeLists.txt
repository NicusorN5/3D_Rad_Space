cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Graphics.DirectX11")

add_library(3DRadSpace.Graphics.DirectX11 STATIC 
	"BlendState.cpp"
	"DepthStencilBuffer.cpp"
	"DepthStencilState.cpp"
	"GraphicsDevice.cpp"
	"IDomainShader.cpp"
	"IFragmentShader.cpp"
	"IGeometryShader.cpp"
	"IHullShader.cpp"
	"IndexBuffer.cpp"
	"IShader.cpp"
	"IVertexShader.cpp"
	"Texture2D.cpp"
	"VertexBuffer.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Graphics.DirectX11 PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace.Graphics.DirectX11 STREQUAL "Debug")
		target_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Graphics.DirectX11 PRIVATE [[E3DRSP_GRAPHICS_DX11_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace.Graphics.DirectX11 PRIVATE USING_DX11=1 _WINDLL=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace.Graphics.DirectX11 PRIVATE USING_VULKAN=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace.Graphics.DirectX11 PRIVATE 3DRadSpace_Core)
target_link_libraries(3DRadSpace.Graphics.DirectX11 PRIVATE 3DRadSpace_Math)
target_link_libraries(3DRadSpace.Graphics.DirectX11 PRIVATE 3DRadSpace_Graphics)
target_include_directories(3DRadSpace.Graphics.DirectX11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)