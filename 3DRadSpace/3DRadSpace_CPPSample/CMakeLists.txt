cmake_minimum_required(VERSION 3.21)

project("3DRadSpace-empty")

file(GLOB_RECURSE 3DRadSpace-empty-src CONFIGURE_DEPENDS "*.cpp" "*.hpp" )
add_executable(3DRadSpace-empty WIN32 ${3DRadSpace-empty-src})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace-empty PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace-empty PRIVATE "/wd4251")
	#Use UNICODE.
	target_compile_definitions(3DRadSpace-empty PUBLIC UNICODE _UNICODE)
	#Fix C4530
	target_compile_options(3DRadSpace-empty PRIVATE "/EHsc")
	# Create separate pdb debug info
	target_compile_options(3DRadSpace-empty PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace-empty PRIVATE "/MP")
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace-empty PRIVATE USING_DX11=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace-empty PRIVATE USING_VULKAN=1)
endif()

#Link 3DRadSpace
target_link_libraries(3DRadSpace-empty PRIVATE 3DRadSpace_Games)
target_include_directories(3DRadSpace-empty PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)