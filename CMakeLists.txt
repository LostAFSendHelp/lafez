cmake_minimum_required(VERSION 3.17)

project(lafez)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_compile_definitions(
    $<$<CONFIG:Debug>:__LZ_DBG>
    $<$<CONFIG:RelWithDebInfo>:__LZ_RELDBG>
)

add_subdirectory(src/lafez-lib)
add_subdirectory(src/example)