add_executable(
    lafez-test

    lafez-test.cpp
)

set_target_properties(lafez-test PROPERTIES EXCLUDE_FROM_ALL TRUE)
find_package(GTest CONFIG REQUIRED)
target_link_libraries(lafez-test PRIVATE lafez-lib GTest::gtest_main GTest::gtest)