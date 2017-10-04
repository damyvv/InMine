cmake_minimum_required (VERSION 2.6)
project (InMine)

# The version number.
set (InMine_VERSION_PREFIX "alpha")
set (InMine_VERSION_MAJOR 0)
set (InMine_VERSION_MINOR 1)
set (InMine_VERSION_PATCH 0)

set (DEVELOPMENT_BUILD TRUE)

set (InMine_VERSION_STRING "${InMine_VERSION_PREFIX}-${InMine_VERSION_MAJOR}.${InMine_VERSION_MINOR}.${InMine_VERSION_PATCH}")
	
if (DEVELOPMENT_BUILD)
	set(InMine_VERSION_STRING "${InMine_VERSION_STRING}-dev")
endif()

message(STATUS "*** Configuring version ${InMine_VERSION_STRING} ***")

configure_file (
	"${PROJECT_SOURCE_DIR}/config/InMineConfig.h.in"
	"${PROJECT_SOURCE_DIR}/include/InMineConfig.h"
)

message(STATUS "Looking for OpenGL...")
# Add OpenGL
find_package(OpenGL REQUIRED)


message(STATUS "Configuring GLFW")
# GLFW Configuration
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/Dependencies/glfw")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable (InMine src/main.cpp)

target_link_libraries (InMine glfw)
target_link_libraries (InMine ${OPENGL_gl_LIBRARY})