cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Objects")

add_library(3DRadSpace.Objects STATIC 
	"Camera.cpp"
	"Counter.cpp"
	"Empty.cpp"
	"ExitFade.cpp"
	"Fog.cpp"
	"Gizmos.cpp"
	"Objects.cpp"
	"Skinmesh.cpp"
	"Skybox.cpp"
	"SkyColor.cpp"
	"SoundEffect.cpp"
	"SoundSource.cpp"
	"Sprite.cpp"
	"TextPrint.cpp"
	"IObject.cpp"
	"IObject2D.cpp"
	"IObject3D.cpp"
	"ObjectList.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Objects PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Objects PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Objects PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Objects PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Objects PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace STREQUAL "Debug")
		target_compile_options(3DRadSpace.Objects PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Objects PRIVATE [[E3DRSP_OBJECTS_EXPORT=__declspec(dllexport)]])
endif()

target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Audio)
target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Content)
target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Content.Assets)
target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Physics)
target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Physics.NVPhysX)
target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Physics.Objects)
target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Objects.Gizmos)
target_include_directories(3DRadSpace.Objects PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)