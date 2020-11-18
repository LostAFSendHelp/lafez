add_executable(
    example

    src/main.cpp
)

set_target_properties(
    example

    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(example
    PRIVATE
    lafez-lib
)