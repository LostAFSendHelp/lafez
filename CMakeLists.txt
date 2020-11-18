cmake_minimum_required(VERSION 3.17)

project(lafez)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(
    $<$<CONFIG:Debug>:__LZ_DBG>
    $<$<CONFIG:RelWithDebInfo>:__LZ_RELDBG>
)

## GLFW check
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/glfw)
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
else()
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW without examples")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW without tests")
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW without docs")
    add_subdirectory(src/vendor/glfw)
endif()

## SPDLOG check
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/spdlog)
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
else()
    add_subdirectory(src/vendor/spdlog)
endif()

## GTEST check
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/spdlog)
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
else()
    set(BUILD_GMOCK OFF CACHE BOOL "Build Gtest without gmock")
    add_subdirectory(src/vendor/gtest)
endif()

add_subdirectory(src/lafez-lib)
add_subdirectory(src/example)
add_subdirectory(src/lafez-test)