# Performance test app
add_executable(
	"perf_test"
	main.cpp
    config.cpp
)

set_target_properties(test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories("perf_test" PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries("perf_test" PRIVATE tren)