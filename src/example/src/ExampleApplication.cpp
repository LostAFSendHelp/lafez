#include "ExampleApplication.hpp"
#include <lafez/core/lafez_renderer.hpp>
#include <lafez/core/lafez_asset.hpp>
#include <lafez/Lafez.hpp>

	
ExampleApplication::ExampleApplication():
    Application(),
	mLayerStack(),
	mDisposeBag() {
	LZ_CLIENT_INFO("EXAMPLE APPLICATION INITIALIZED");
}

ExampleApplication::~ExampleApplication() {
	LZ_CLIENT_INFO("EXAMPLE APPLICATION TERMIANTED");
}

void ExampleApplication::startUp() {
	Lafez::startUp(LZ_PLATFORM_GL);
	auto eventCenter = Lafez::EventCenter::getInstance();
    auto imguiLayer = Lafez::Layer::create<Lafez::ImGuiLayer>("Imgui Layer");
    mLayerStack.pushLayers(imguiLayer);

    auto closeSub = eventCenter->subscribe([=](Lafez::Event& event) {
        if (event.mType == Lafez::EventType::Key) {
            auto keyEvent = (Lafez::KeyEvent&)event;
            if (keyEvent.mKeyCode == Lafez::Key::getInstance()->Q && keyEvent.mAction == Lafez::ButtonAction::Release) {
                Lafez::Window::close();
            }
        }
    });

    mDisposeBag.dispose(closeSub);
}

void ExampleApplication::run() {
    float data[] = {
        .0f, .5f, .0f, 1.0f, .0f, .0f,
        -.5f, -.5f, .0f, .0f, 1.0f, .0f,
        .5f, -.5f, .0f, .0f, .0f, 1.0f
    };

    uint32_t indices[] = { 0, 1, 2 };

    auto vertexArray = LzUniPtr<Lafez::VertexArray>{ Lafez::RendererBackend::genVertexArray() };
    vertexArray->bind();
    auto arrayBuffer = LzShrPtr<Lafez::ArrayBuffer>{ Lafez::RendererBackend::genArrayBuffer(data, sizeof(float) * 18, 3) };
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
        Lafez::RendererBackend::drawVertexArray(*vertexArray);
        mLayerStack.update();
    }
}

void ExampleApplication::shutDown() {
	mLayerStack.flush();
	Lafez::shutDown();
}

Lafez::Application* Lafez::createApplication() {
    return new ExampleApplication;
}