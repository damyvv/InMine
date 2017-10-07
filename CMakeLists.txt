cmake_minimum_required (VERSION 2.6)
project (InMine)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
endif()

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

# GLFW Configuration
message(STATUS "Configuring GLFW...")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/Dependencies/glfw")

# GLEW Configuration
message(STATUS "Configuring GLEW...")
set(glew-cmake_BUILD_SHARED         OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_STATIC         ON  CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_SINGLE_CONTEXT ON  CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_MULTI_CONTEXT  OFF CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/Dependencies/glew")

# glm Configuration
message(STATUS "Adding glm...")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/glm")

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE InMine_SOURCE
	"src/*.cpp"
	"src/*.h"
)

if (MSVC)
	message(STATUS "Generating visual studio filters...")
	foreach(source IN LISTS InMine_SOURCE)
		file(RELATIVE_PATH path "${PROJECT_SOURCE_DIR}/src" ${source})
		get_filename_component(source_path "${path}" PATH)
		string(REPLACE "/" "\\" source_path_msvc "${source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()

# Copy resources
message(STATUS "Coping resources...")
file(COPY "res" DESTINATION "${CMAKE_BINARY_DIR}")

add_executable (InMine ${InMine_SOURCE})

target_link_libraries (InMine libglew_static)
target_link_libraries (InMine glfw)
target_link_libraries (InMine ${OPENGL_gl_LIBRARY})