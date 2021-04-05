add_executable(
    example

    src/ExampleApplication.hpp
    src/ExampleApplication.cpp
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

install(
    TARGETS example lafez-lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY ${LAFEZ_ASSET_PATH}/renderer/shaders
    DESTINATION bin/assets
)