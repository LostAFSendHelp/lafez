#include <lafez/utils/Log.hpp>
#include <lafez/core/lafez_event.hpp>
#include <lafez/core/lafez_foundation.hpp>
#include <lafez/core/lafez_layer.hpp>
#include <lafez/core/lafez_renderer.hpp>
#include <iostream>

int main() {
    Lafez::Log::init();
    
    LZ_ENGINE_INFO("Test Info message");
    LZ_ENGINE_WARN("Test Warning message");
    LZ_ENGINE_ERR("Test Error message");
    
    LZ_CLIENT_INFO("Test Info message");
    LZ_CLIENT_WARN("Test Warning message");
    LZ_CLIENT_ERR("Test Error message");


    Lafez::startUp(LZ_PLATFORM_GL);

    Lafez::LayerStack layerStack{ };
    
    layerStack.pushLayers(Lafez::Layer::create<Lafez::ImGuiLayer>(LzString("test layer")));

    Lafez::DisposeBag bag{ };
    auto eventCenter = Lafez::EventCenter::getInstance();
    
    auto closeSub = eventCenter->subscribe([=](Lafez::Event& event) {
        if (event.mType == Lafez::EventType::Key) {
            auto keyEvent = (Lafez::KeyEvent&)event;
            if (keyEvent.mKeyCode == 81 && keyEvent.mAction == Lafez::ButtonAction::Release) {
                Lafez::Window::close();
            }
        }
    });

    auto testSub = eventCenter->subscribe([](Lafez::Event& event) {
        LZ_CLIENT_INFO(event.toString());
    });

    bag.dispose(closeSub);

    while (!Lafez::Window::shouldClose()) {
        Lafez::Window::update();
        layerStack.update();
    }

    layerStack.flush();
    Lafez::shutDown();

    return 0;
}