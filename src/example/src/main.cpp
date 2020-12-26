#include <lafez/utils/Log.hpp>
#include <lafez/core/lafez_event.hpp>
#include <lafez/core/lafez_foundation.hpp>
#include <lafez/core/lafez_layer.hpp>
#include <lafez/core/lafez_renderer.hpp>
#include <lafez/core/lafez_asset.hpp>
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
    float data[] = {
        .0f, .5f, .0f, 1.0f, .0f, .0f,
        -.5f, -.5f, .0f, .0f, 1.0f, .0f,
        .5f, -.5f, .0f, .0f, .0f, 1.0f
    };

    uint32_t indices[] = { 0, 1, 2 };

    auto vertexArray = LzUniPtr<Lafez::VertexArray>{ Lafez::RendererBackend::genVertexArray() };
    vertexArray->bind();
    auto arrayBuffer = LzShrPtr<Lafez::ArrayBuffer>{ Lafez::RendererBackend::genArrayBuffer(data, sizeof(float) * 18) };
    arrayBuffer->bind();
    Lafez::VertexBufferLayout layout{ { LZ_PTYPE_VEC3F, LZ_PTYPE_VEC3F } };
    arrayBuffer->setBufferLayout(layout);
    auto indexBuffer = LzShrPtr<Lafez::IndexBuffer>{ Lafez::RendererBackend::genIndexBuffer(indices, 3) };
    indexBuffer->bind();
    vertexArray->addArrayBuffer(arrayBuffer);
    vertexArray->addIndexBuffer(indexBuffer);

    auto shader = LzUniPtr<Lafez::Shader>{
        Lafez::RendererBackend::genShader(
            "basic shader",
            Lafez::Asset::getString("assets/shaders/vertex_shader.glsl"),
            Lafez::Asset::getString("assets/shaders/fragment_shader.glsl")
        )
    };
    shader->use();

    while (!Lafez::Window::shouldClose()) {
        Lafez::Window::update();
        Lafez::RendererBackend::renderExample(*vertexArray);
        layerStack.update();
    }

    layerStack.flush();
    Lafez::shutDown();

    return 0;
}