cmake_minimum_required(VERSION 3.21)

project("3DRadSpace")

#https://stackoverflow.com/questions/16398937/cmake-and-finding-other-projects-and-their-dependencies
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

#https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(Engine3DRadSpace/Core)
add_subdirectory(Engine3DRadSpace/Math)
add_subdirectory(Engine3DRadSpace/Reflection)
add_subdirectory(Engine3DRadSpace/Audio)
add_subdirectory(Engine3DRadSpace/Graphics)
add_subdirectory(Engine3DRadSpace/Content)
add_subdirectory(Engine3DRadSpace/Physics)
add_subdirectory(Engine3DRadSpace/Input)
add_subdirectory(Engine3DRadSpace/Objects)
add_subdirectory(Engine3DRadSpace/Native)
add_subdirectory(Engine3DRadSpace/Projects)
add_subdirectory(Engine3DRadSpace/Scripting)
add_subdirectory(Engine3DRadSpace/Plugins)
add_subdirectory(Engine3DRadSpace/Games)

add_subdirectory(3DRadSpace_Editor_WindowsDX11)
add_subdirectory(3DRadSpace_Compiler)
add_subdirectory(Engine3DRadSpace_Tests)
add_subdirectory(3DRadSpace_CPPSample)
add_subdirectory(3DRadSpace_AngelscriptPlugin)