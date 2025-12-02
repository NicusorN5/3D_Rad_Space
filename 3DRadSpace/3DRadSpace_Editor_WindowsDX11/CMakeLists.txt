cmake_minimum_required(VERSION 3.21)

project("3DRadSpace-editor")

file(GLOB_RECURSE 3DRadSpace-editor-src CONFIGURE_DEPENDS "*.cpp" "*.hpp" )
add_executable(3DRadSpace-editor WIN32 ${3DRadSpace-editor-src})

target_sources(3DRadSpace-editor PRIVATE 3DRadSpace_Editor_WindowsDX11.rc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace-editor PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace-editor PRIVATE "/wd4251")
	#Use UNICODE.
	target_compile_definitions(3DRadSpace-editor PUBLIC UNICODE _UNICODE)
	#Fix C4530
	target_compile_options(3DRadSpace-editor PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace-editor PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace-editor PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace-editor STREQUAL "Debug")
		target_compile_options(3DRadSpace-editor PRIVATE "/fsanitize=address")
	endif()
endif()

#Link 3DRadSpace
target_link_libraries(3DRadSpace-editor PRIVATE 3DRadSpace.Objects)
target_link_libraries(3DRadSpace-editor PRIVATE 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace-editor PRIVATE 3DRadSpace.Graphics.DirectX11)
target_link_libraries(3DRadSpace-editor PRIVATE 3DRadSpace.Graphics.Primitives)
target_link_libraries(3DRadSpace-editor PRIVATE 3DRadSpace.Graphics.Rendering)
target_link_libraries(3DRadSpace-editor PRIVATE 3DRadSpace.Games)
target_include_directories(3DRadSpace-editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace-editor PRIVATE nlohmann_json::nlohmann_json)

#Copy assets
#file(COPY ../Data DESTINATION ${CMAKE_BINARY_DIR})