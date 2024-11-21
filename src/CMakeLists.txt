set(RENDERER_SOURCE_FILES
	resources.cpp
	resources.hpp
	color.cpp
	color.hpp
	frame.cpp
	frame.hpp
	frame_unit.cpp
	frame_unit.hpp
	renderer.cpp
	renderer.hpp
	terminal.cpp
	terminal.hpp
	utils.cpp
	utils.hpp
)

set(RENDERER_API_FILES
	../include/terminal/renderer.hpp
	../include/terminal/utils.hpp
	../include/terminal/resources.hpp
)

# Hide internal functions
# todo need to investigate this more
# https://gcc.gnu.org/wiki/Visibility
# set(CMAKE_C_VISIBILITY_PRESET hidden)
# set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(tren ${RENDERER_SOURCE_FILES} ${RENDERER_API_FILES})

# Generate box2d_export.h to handles shared library builds
# turned this off to make Box2D easier to use without cmake
# include(GenerateExportHeader)
# generate_export_header(box2d)

target_include_directories(tren
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CMAKE_DEBUG_POSTFIX "d")

# Renderer uses C17
set_target_properties(tren PROPERTIES
	C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS YES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

if (MSVC)
	message(STATUS "TRen on MSVC")	
	if (BUILD_SHARED_LIBS)
		# this is needed by DLL users to import Box2D symbols
		#target_compile_definitions(box2d INTERFACE BOX2D_DLL)
	endif()

	# All warnings
	target_compile_options(tren PRIVATE /W4)

endif()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${RENDERER_SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include" PREFIX "include" FILES ${RENDERER_API_FILES})

add_library(tren::tren ALIAS tren)
