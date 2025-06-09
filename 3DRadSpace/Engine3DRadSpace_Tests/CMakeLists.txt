cmake_minimum_required(VERSION 3.14)
project("3DRadSpace-tests")

file(GLOB 3DRadSpace_tests_src CONFIGURE_DEPENDS "*.cpp")
add_executable(3DRadSpace-tests ${3DRadSpace_tests_src})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace-tests PROPERTY CXX_STANDARD 23)
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace-tests PRIVATE USING_DX11=1)
elseif(LINUX)
	target_compile_definitions(3DRadSpace-tests PRIVATE USING_VULKAN=1)
endif()

if(MSVC)
	#Fix C4530
	target_compile_options(3DRadSpace-tests PRIVATE "/EHsc")
	# Create separate pdb debug info files
	target_compile_options(3DRadSpace-tests PRIVATE "/Zi")

	# Multiprocessor build
	add_compile_options(3DRadSpace-tests PRIVATE "/MP")
endif()

#Link 3DRadSpace
target_link_libraries(3DRadSpace-tests PRIVATE 3DRadSpace_Games)
target_include_directories(3DRadSpace-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

enable_testing()
option(3DRadSpace-tests "Build unit tests" ON)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(3DRadSpace-tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(3DRadSpace-tests)

install(FILES $<TARGET_RUNTIME_DLLS:3DRadSpace-editor> TYPE BIN)