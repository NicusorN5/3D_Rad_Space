cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Reflection")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace_Reflection STATIC ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace_Reflection PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_Reflection PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace_Reflection PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace_Reflection PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace_Reflection PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(3DRadSpace STREQUAL "Debug")
		target_compile_options(3DRadSpace_Reflection PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace_Reflection PRIVATE [[E3DRSP_REFLECTION_EXPORT=__declspec(dllexport)]])
endif()

target_link_libraries(3DRadSpace_Reflection PRIVATE 3DRadSpace_Math)
target_include_directories(3DRadSpace_Reflection PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace_Reflection PRIVATE nlohmann_json::nlohmann_json)