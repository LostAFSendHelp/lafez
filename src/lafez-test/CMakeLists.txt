include(GoogleTest)

add_executable(
    lafez-test

    lafez_test.cpp
    core-test/event/MouseEventTest.hpp
    core-test/event/KeyEventTest.hpp
    core-test/event/ApplicationEventTest.hpp
)

target_precompile_headers(
    lafez-test

    PRIVATE
    lafez_test_pch.hpp
)

set_target_properties(
    lafez-test
    
    PROPERTIES
    EXCLUDE_FROM_ALL TRUE
)

find_package(GTest CONFIG REQUIRED)

target_include_directories(
    lafez-test

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    lafez-test
 
    PRIVATE
    lafez-lib
    GTest::gtest_main
    GTest::gtest
)

gtest_discover_tests(
    lafez-test

    WORKING_DIRECTORY ${PROJECT_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
)