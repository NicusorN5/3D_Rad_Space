cmake_minimum_required(VERSION 3.21)

project("3DRadSpace-angelscript")

file(GLOB_RECURSE 3DRadSpace-angelscript-src CONFIGURE_DEPENDS "*.cpp" "*.hpp" )
add_library(3DRadSpace-angelscript SHARED ${3DRadSpace-angelscript-src})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace-angelscript PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace-angelscript PRIVATE "/wd4251")
	#Use UNICODE.
	target_compile_definitions(3DRadSpace-angelscript PUBLIC UNICODE _UNICODE)
	#Fix C4530
	target_compile_options(3DRadSpace-angelscript PRIVATE "/EHsc")
	# Create separate pdb debug info
	target_compile_options(3DRadSpace-angelscript PRIVATE "/Zi")

	#MSVC doesn't define NDEBUG itself, dirty hack.
	if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		target_compile_definitions(3DRadSpace-angelscript PUBLIC NDEBUG 1)
	endif()
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace-angelscript PRIVATE USING_DX11=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace-angelscript PRIVATE USING_VULKAN=1)
endif()

#Link 3DRadSpace
target_link_libraries(3DRadSpace-angelscript PRIVATE 3DRadSpace)
target_include_directories(3DRadSpace-angelscript PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Add Angelscript
find_package(Angelscript CONFIG REQUIRED)
target_link_libraries(3DRadSpace-angelscript PRIVATE Angelscript::angelscript)