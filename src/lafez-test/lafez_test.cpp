#include <core-test/event_tests.hpp>
#include <core-test/layer_tests.hpp>
#include <lafez/utils/Log.hpp>

int main(int argc, char **argv) {
    ::Lafez::Log::setClientLogLevel(spdlog::level::critical);
    ::Lafez::Log::setEngineLogLevel(spdlog::level::critical);
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}