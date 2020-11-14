#include <core-test/event/mouse_event_test.hpp>
#include <core-test/event/key_event_test.hpp>
#include <core-test/event/application_event_test.hpp>
#include <lafez/utils/Log.hpp>

int main(int argc, char **argv) {
    ::Lafez::Log::setClientLogLevel(spdlog::level::critical);
    ::Lafez::Log::setEngineLogLevel(spdlog::level::critical);
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}