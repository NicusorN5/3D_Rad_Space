cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Objects")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace.Objects STATIC ${SOURCE_FILES})

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
target_link_libraries(3DRadSpace.Objects PRIVATE 3DRadSpace.Reflection)
target_include_directories(3DRadSpace.Objects PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)