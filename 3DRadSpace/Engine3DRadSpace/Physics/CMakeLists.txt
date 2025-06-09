cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Physics")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace_Physics STATIC ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace_Physics PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_Physics PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace_Physics PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace_Physics PRIVATE "/Zi")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace STREQUAL "Debug")
		target_compile_options(3DRadSpace_Physics PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace_Physics PRIVATE [[E3DRSP_PHYSICS_EXPORT=__declspec(dllexport)]])
endif()

find_package(unofficial-omniverse-physx-sdk CONFIG REQUIRED)
target_link_libraries(3DRadSpace_Physics PRIVATE unofficial::omniverse-physx-sdk::sdk)

target_link_libraries(3DRadSpace_Physics PRIVATE 3DRadSpace_Math)
target_include_directories(3DRadSpace_Physics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)