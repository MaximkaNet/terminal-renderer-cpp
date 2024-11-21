# Renderer unit test app
add_executable(test
	main.cpp
)

set_target_properties(test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Special access to Box2D internals for testing
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(test PRIVATE renderer Catch2::Catch2WithMain)