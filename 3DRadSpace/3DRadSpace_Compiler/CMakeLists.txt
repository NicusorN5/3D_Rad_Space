cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Compiler")

file(GLOB_RECURSE 3DRadSpace.Compiler-src CONFIGURE_DEPENDS "*.cpp" "*.hpp" )
add_executable(3DRadSpace.Compiler ${3DRadSpace.Compiler-src})
target_sources(3DRadSpace.Compiler PRIVATE 3DRadSpace_Compiler.rc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Compiler PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Compiler PRIVATE "/wd4251")
	#Use UNICODE.
	target_compile_definitions(3DRadSpace.Compiler PUBLIC UNICODE _UNICODE)
	#Fix C4530
	target_compile_options(3DRadSpace.Compiler PRIVATE "/EHsc")
	# Create separate pdb debug info compiler
	target_compile_options(3DRadSpace.Compiler PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Compiler PRIVATE "/MP")
endif()

#Link 3DRadSpace
#target_link_libraries(3DRadSpace.Compiler PRIVATE 3DRadSpace)
#target_include_directories(3DRadSpace.Compiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Compiler PRIVATE nlohmann_json::nlohmann_json)