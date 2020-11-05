#include <lafez/lafez.hpp>
#include <lafez/utils/Log.hpp>
#include <iostream>

int main() {
    Lafez::Log::init();
    
    LZ_ENGINE_INFO("Test Info message");
    LZ_ENGINE_WARN("Test Warning message");
    LZ_ENGINE_ERR("Test Error message");
    
    LZ_CLIENT_INFO("Test Info message");
    LZ_CLIENT_WARN("Test Warning message");
    LZ_CLIENT_ERR("Test Error message");

    return 0;
}