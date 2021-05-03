#include "ExampleApplication.hpp"
#include <lafez/core/lafez_renderer.hpp>
#include <lafez/core/lafez_asset.hpp>
#include <lafez/core/lafez_event.hpp>
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
	Lafez::startUp(LZ_PLATFORM_DX);
    auto baseWindowName = Lafez::Window::getName();
	auto eventCenter = Lafez::EventCenter::getInstance();
    //auto imguiLayer = Lafez::Layer::create<Lafez::ImGuiLayer>("Imgui Layer");
    //mLayerStack.pushLayers(imguiLayer);

    auto closeSub = eventCenter->subscribe([=](Lafez::Event& event) {
        if (event.mType == Lafez::EventType::Key) {
            auto keyEvent = (Lafez::KeyEvent&)event;
            if (keyEvent.mKeyCode == Lafez::Key::getInstance()->Q && keyEvent.mAction == Lafez::ButtonAction::Release) {
                Lafez::Window::close();
            }
        }

        if (event.mType == Lafez::EventType::WindowClose) {
            Lafez::Window::close();
        }

        if (event.mType == LZT_KEY
            || event.mType == LZT_WINDOW_RESIZE
            || event.mType == LZT_MOUSE_BUTTON
            || event.mType == LZT_MOUSE_SCROLL) {
            LZ_CLIENT_INFO(event.toString());
        }

        if (event.mType == LZT_MOUSE_MOVE) {
            auto mouseEvent = dynamic_cast<Lafez::MouseMoveEvent*>(&event);
            Lafez::Window::setName(
                fmt::format(
                    "{0} - Cursor at ({1}, {2})",
                    baseWindowName,
                    mouseEvent->mX,
                    mouseEvent->mY
                ).c_str()
            );
        }
    });

    mDisposeBag.dispose(closeSub);
}

void ExampleApplication::run() {
    float data[] = {
        .0f, .5f, .0f, 1.0f, .0f, .0f,
        .5f, -.5f, .0f, .0f, .0f, 1.0f,
        -.5f, -.5f, .0f, .0f, 1.0f, .0f,
    };

    uint32_t indices[] = { 0, 1, 2 };

    auto vertexArray = LzUniPtr<Lafez::VertexArray>{ Lafez::RendererBackend::genVertexArray() };
    //vertexArray->bind();
    auto arrayBuffer = LzShrPtr<Lafez::ArrayBuffer>{ Lafez::RendererBackend::genArrayBuffer(data, sizeof(float) * 18, 3) };
    arrayBuffer->bind();

    Lafez::VertexBufferLayout layout{
        {
            { "VS_POSITION", LZ_PTYPE_VEC3F },
            { "VS_COLOR", LZ_PTYPE_VEC3F }
        } 
    };
    //auto indexBuffer = LzShrPtr<Lafez::IndexBuffer>{ Lafez::RendererBackend::genIndexBuffer(indices, 3) };
    //indexBuffer->bind();
    //vertexArray->addIndexBuffer(indexBuffer);

    auto shader = LzUniPtr<Lafez::Shader>{
        Lafez::RendererBackend::genShader(
            "basic shader",
            Lafez::Asset::getString("assets/shaders/hlsl/vertex_shader.hlsl"),
            Lafez::Asset::getString("assets/shaders/hlsl/fragment_shader.hlsl")
        )
    };

    shader->use();
    arrayBuffer->setBufferLayout(&layout, shader.get());
    vertexArray->addArrayBuffer(arrayBuffer);

    while (!Lafez::Window::shouldClose()) {
        static auto spice = .0f;
        Lafez::Window::update();
        Lafez::RendererBackend::clearBuffer(std::sinf(spice), .2f, std::cosf(spice), 1.0f);
        Lafez::RendererBackend::drawVertexArray(vertexArray.get());

        // Render shits
        Lafez::RendererBackend::swapBuffers();
        spice += .01f;
    }
}

void ExampleApplication::shutDown() {
	//mLayerStack.flush();
	Lafez::shutDown();
}

Lafez::Application* Lafez::createApplication() {
    return new ExampleApplication;
}