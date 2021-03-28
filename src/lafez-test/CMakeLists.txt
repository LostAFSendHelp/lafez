include(GoogleTest)

add_executable(
    lafez-test

    lafez_test.cpp

    core-test/event_tests.hpp
    core-test/event/EventControlTest.hpp
    core-test/event/MouseEventTest.hpp
    core-test/event/KeyEventTest.hpp
    core-test/event/ApplicationEventTest.hpp

    core-test/layer_tests.hpp
    core-test/layers/mnl-mocks/ConsumingLayer.hpp
    core-test/layers/mnl-mocks/NonConsumingLayer.hpp
    core-test/layers/tests/LayerStackTest.hpp

    core-test/foundation_tests.hpp
    core-test/foundation/mnl-mocks/WindowMock.hpp
    core-test/foundation/mnl-mocks/InputMock.hpp
    core-test/foundation/mnl-mocks/ImGuiBackendMock.hpp
    core-test/foundation/tests/WindowTest.hpp
    core-test/foundation/tests/InputTest.hpp
    core-test/foundation/tests/ImGuiBackendTest.hpp

    core-test/renderer/mnl-mocks/RendererBackendMock.hpp
    core-test/renderer/tests/BufferTest.hpp
    core-test/renderer/tests/ShaderTest.hpp
    core-test/renderer/tests/VertexArrayTest.hpp
)

target_precompile_headers(
    lafez-test

    PRIVATE
    lafez_test_pch.hpp
)

set_target_properties(
    lafez-test
    
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(
    lafez-test

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    lafez-test
 
    PRIVATE
    lafez-lib
    gtest
)

gtest_discover_tests(
    lafez-test

    WORKING_DIRECTORY ${PROJECT_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
)