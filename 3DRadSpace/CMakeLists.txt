cmake_minimum_required(VERSION 3.21)

project("3DRadSpace")

#https://stackoverflow.com/questions/16398937/cmake-and-finding-other-projects-and-their-dependencies
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

add_subdirectory(Engine3DRadSpace)
add_subdirectory(3DRadSpace_Editor_WindowsDX11)
add_subdirectory(Engine3DRadSpace_Tests)