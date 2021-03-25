cmake_minimum_required(VERSION 3.17)

project(lafez)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

add_compile_definitions(
    $<$<CONFIG:Debug>:__LZ_DBG>
    $<$<CONFIG:RelWithDebInfo>:__LZ_RELDBG>
)










## ---------------------------------------LIBRARIES---------------------------------------

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

## glad check
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/glad)
    message(FATAL_ERROR "Could not find GLAD")
else()
    add_subdirectory(src/vendor/glad)
endif()

## imgui check
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/imgui)
    message(FATAL_ERROR "Could not find IMGUI")
else()
    add_subdirectory(src/vendor/imgui)
endif()

## glm check
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/glm)
    message(FATAL_ERROR "Could not find GLM")
else()
    add_subdirectory(src/vendor/glm)
endif()

## ---------------------------------------LIBRARIES---------------------------------------









## ---------------------------------------SUBDIRS---------------------------------------

add_subdirectory(src/lafez-lib)
add_subdirectory(src/example)
add_subdirectory(src/lafez-test)

## ---------------------------------------SUBDIRS---------------------------------------










## --------------------------------------INSTALLS---------------------------------------

install(
    TARGETS example
    RUNTIME DESTINATION bin
)

## --------------------------------------INSTALLS---------------------------------------