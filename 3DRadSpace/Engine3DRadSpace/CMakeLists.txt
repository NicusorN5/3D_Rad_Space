cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace SHARED ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace PRIVATE "/EHsc")
	# Create separate pdb debug info files
	target_compile_options(3DRadSpace PRIVATE "/Zi")

	#MSVC doesn't define NDEBUG itself, dirty hack.
	if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		target_compile_definitions(3DRadSpace PUBLIC NDEBUG 1)
	endif()
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace PRIVATE USING_DX11=1 _WINDLL=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace PRIVATE USING_VULKAN=1)
endif()

#
#Dependencies 
#

#assimp
find_package(assimp CONFIG REQUIRED)
target_link_libraries(3DRadSpace PRIVATE assimp::assimp)

#DirectXTK
find_package(directxtk CONFIG REQUIRED)
target_link_libraries(3DRadSpace PRIVATE Microsoft::DirectXTK)

#FreeType
find_package(freetype CONFIG REQUIRED)
target_link_libraries(3DRadSpace PRIVATE Freetype::Freetype)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace PRIVATE nlohmann_json::nlohmann_json)

#OpenAL-Soft
find_package(OpenAL CONFIG REQUIRED)
target_link_libraries(3DRadSpace PRIVATE OpenAL::OpenAL)

#NVidia PhysX
find_package(unofficial-omniverse-physx-sdk CONFIG REQUIRED)
target_link_libraries(3DRadSpace PRIVATE unofficial::omniverse-physx-sdk::sdk)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace PRIVATE nlohmann_json::nlohmann_json)