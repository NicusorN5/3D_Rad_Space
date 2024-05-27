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

add_subdirectory(Engine3DRadSpace)
add_subdirectory(3DRadSpace_Editor_WindowsDX11)
add_subdirectory(Engine3DRadSpace_Tests)