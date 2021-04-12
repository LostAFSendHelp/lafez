set(
    EXAMPLE_SOURCES
    src/ExampleApplication.cpp
)

set(
    EXAMPLE_HEADER
    src/ExampleApplication.hpp
)

if(WIN32)
    add_executable(
        example WIN32

        ${EXAMPLE_HEADER}
        ${EXAMPLE_SOURCES}
    )
else()
    add_executable(
        example

        ${EXAMPLE_HEADER}
        ${EXAMPLE_SOURCES}
    )
endif(WIN32)

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