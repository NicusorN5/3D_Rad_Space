cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Graphics.Primitives")

add_library(3DRadSpace.Graphics.Primitives STATIC 
	"Arrow.cpp"
	"Box.cpp"
	"CilindricalBillboard.cpp"
	"Circle.cpp"
	"CubeMapSkybox.cpp"
	"Cylinder.cpp"
	"IPrimitive.cpp"
	"LineList.cpp"
	"LineStrip.cpp"
	"Plane.cpp"
	"Sphere.cpp"
	"SphericalBillboard.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Graphics.Primitives PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Graphics.Primitives PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Graphics.Primitives PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Graphics.Primitives PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Graphics.Primitives PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace.Graphics.Primitives STREQUAL "Debug")
		target_compile_options(3DRadSpace.Graphics.Primitives PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Graphics.Primitives PRIVATE [[E3DRSP_GRAPHICS_PRIMITIVES_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace.Graphics.Primitives PRIVATE _WINDLL=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace.Graphics.Primitives PRIVATE 3DRadSpace.Core)
target_link_libraries(3DRadSpace.Graphics.Primitives PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Graphics.Primitives PRIVATE 3DRadSpace.Math)
target_include_directories(3DRadSpace.Graphics.Primitives PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)