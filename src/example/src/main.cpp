#include <lafez.hpp>
#include <utils/log.hpp>
#include <iostream>

int main() {
    Lafez::init();
    Lafez::Log::init();
    Lafez::Log::getEngineLog()->info("Test Info message");
    Lafez::Log::getClientLog()->warn("Test Warning message");
    return 0;
}