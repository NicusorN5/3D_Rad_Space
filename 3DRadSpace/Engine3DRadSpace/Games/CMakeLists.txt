cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Games")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace_Games STATIC ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace_Games PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_Games PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace_Games PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace_Games PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace_Games PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace_Games STREQUAL "Debug")
		target_compile_options(3DRadSpace_Games PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace_Games PRIVATE [[E3DRSP_GAMES_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace_Games PRIVATE _WINDLL=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace_Games PRIVATE 3DRadSpace_Audio)
target_link_libraries(3DRadSpace_Games PRIVATE 3DRadSpace_Graphics)
target_link_libraries(3DRadSpace_Games PRIVATE 3DRadSpace_Content)
target_link_libraries(3DRadSpace_Games PRIVATE 3DRadSpace_Objects)
target_link_libraries(3DRadSpace_Games PRIVATE 3DRadSpace_Content)
target_link_libraries(3DRadSpace_Games PRIVATE 3DRadSpace_Input)
target_link_libraries(3DRadSpace_Games PRIVATE 3DRadSpace_Native)
target_link_libraries(3DRadSpace_Games PRIVATE 3DRadSpace_Projects)
target_link_libraries(3DRadSpace_Games PRIVATE 3DRadSpace_Reflection)
target_include_directories(3DRadSpace_Games PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace_Games PRIVATE nlohmann_json::nlohmann_json)