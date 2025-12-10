cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Physics.NVPhysX")

add_library(3DRadSpace.Physics.NVPhysX STATIC
	"DynamicRigidbody.cpp"
	"PhysicsEngine.cpp"
	"StaticRigidbody.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Physics.NVPhysX PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Physics.NVPhysX PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Physics.NVPhysX PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Physics.NVPhysX PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Physics.NVPhysX PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace STREQUAL "Debug")
		target_compile_options(3DRadSpace.Physics.NVPhysX PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Physics.NVPhysX PRIVATE [[E3DRSP_PHYSICS_NVPHYSX_EXPORT=__declspec(dllexport)]])
endif()

find_package(unofficial-omniverse-physx-sdk CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Physics.NVPhysX PRIVATE unofficial::omniverse-physx-sdk::sdk)

target_link_libraries(3DRadSpace.Physics.NVPhysX PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Physics.NVPhysX PRIVATE 3DRadSpace.Physics)
target_link_libraries(3DRadSpace.Physics.NVPhysX PRIVATE 3DRadSpace.Logging)
target_link_libraries(3DRadSpace.Physics.NVPhysX PRIVATE 3DRadSpace.Objects)
target_include_directories(3DRadSpace.Physics.NVPhysX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)