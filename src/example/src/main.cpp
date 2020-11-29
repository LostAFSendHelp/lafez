#include <lafez/utils/Log.hpp>
#include <lafez/core/lafez_event.hpp>
#include <lafez/core/lafez_window.hpp>
#include <lafez/core/lafez_layer.hpp>
#include <iostream>

int main() {
    Lafez::Log::init();
    
    LZ_ENGINE_INFO("Test Info message");
    LZ_ENGINE_WARN("Test Warning message");
    LZ_ENGINE_ERR("Test Error message");
    
    LZ_CLIENT_INFO("Test Info message");
    LZ_CLIENT_WARN("Test Warning message");
    LZ_CLIENT_ERR("Test Error message");


    LzShrPtr<Lafez::Window> window{ Lafez::Window::createWindow("LAFEZ", 800, 600) };
    window->init();

    Lafez::LayerStack layerStack{ };
    
    layerStack.pushLayers(Lafez::Layer::create<Lafez::ImGuiLayer>(LzString("test layer"), window));

    Lafez::DisposeBag bag{ };
    auto eventCenter = Lafez::EventCenter::getInstance();
    
    auto closeSub = eventCenter->subscribe([=](Lafez::Event& event) {
        if (event.mType == Lafez::EventType::Key) {
            auto keyEvent = (Lafez::KeyEvent&)event;
            if (keyEvent.mKeyCode == GLFW_KEY_Q && keyEvent.mAction == Lafez::ButtonAction::Release) {
                window->close();
            }
        }
    });

    auto testSub = eventCenter->subscribe([](Lafez::Event& event) {
        LZ_CLIENT_INFO(event.toString());
    });

    bag.dispose(closeSub);

    while (!window->shouldClose()) {
        window->update();
        layerStack.update();
    }

    layerStack.flush();
    window->terminate();

    return 0;
}