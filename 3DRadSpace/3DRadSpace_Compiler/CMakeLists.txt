cmake_minimum_required(VERSION 3.21)

project("3DRadSpace-compiler")

file(GLOB_RECURSE 3DRadSpace-compiler-src CONFIGURE_DEPENDS "*.cpp" "*.hpp" )
add_executable(3DRadSpace-compiler ${3DRadSpace-compiler-src})
target_sources(3DRadSpace-compiler PRIVATE 3DRadSpace_Compiler.rc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace-compiler PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace-compiler PRIVATE "/wd4251")
	#Use UNICODE.
	target_compile_definitions(3DRadSpace-compiler PUBLIC UNICODE _UNICODE)
	#Fix C4530
	target_compile_options(3DRadSpace-compiler PRIVATE "/EHsc")
	# Create separate pdb debug info compiler
	target_compile_options(3DRadSpace-compiler PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace-compiler PRIVATE "/MP")
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace-compiler PRIVATE USING_DX11=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace-compiler PRIVATE USING_VULKAN=1)
endif()

#Link 3DRadSpace
#target_link_libraries(3DRadSpace-compiler PRIVATE 3DRadSpace)
#target_include_directories(3DRadSpace-compiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace-compiler PRIVATE nlohmann_json::nlohmann_json)