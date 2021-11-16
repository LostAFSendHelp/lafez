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
	LZ_CLIENT_INFO("EXAMPLE APPLICATION TERMINATED");
}

void ExampleApplication::startUp() {
    const auto configs = Lafez::EngineConfigs::loadDefault();
	Lafez::startUp(configs);
    auto baseWindowName = Lafez::Window::getName();
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
                Lafez::Log::raw(
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
    auto shader = LzUniPtr<Lafez::Shader>{ Lafez::RendererBackend::genDefaultShader() };
    shader->use();

    float data[] = {
        .0f, .75f, .0f, 1.0f, .0f, .0f,
        .25f, .25f, .0f, .0f, .0f, 1.0f,
        -.25f, .25f, .0f, .0f, 1.0f, .0f,
    };

    float anotherData[] = {
        .0f, -.25f, .0f, 1.0f, .0f, .0f,
        .25f, -.75f, .0f, .0f, .0f, 1.0f,
        -.25f, -.75f, .0f, .0f, 1.0f, .0f,
    };

    Lafez::VertexBufferLayout layout{
        {
            { "VS_POSITION", LZ_PTYPE_VEC3F },
            { "VS_COLOR", LZ_PTYPE_VEC3F }
        }
    };

    uint32_t indices[] = { 0, 1, 2 };

    auto vertexArray = LzUniPtr<Lafez::VertexArray>{ Lafez::RendererBackend::genVertexArray() };
    auto arrayBuffer = LzShrPtr<Lafez::ArrayBuffer>{ Lafez::RendererBackend::genArrayBuffer(data, sizeof(float) * 18, 3) };
    auto indexBuffer = LzShrPtr<Lafez::IndexBuffer>{ Lafez::RendererBackend::genIndexBuffer(indices, 3) };
    vertexArray->addIndexBuffer(indexBuffer);
    vertexArray->addArrayBuffer(arrayBuffer);
    arrayBuffer->setBufferLayout(layout, shader.get()); // On DX layout is reusable, so the next layout setting call is not necessary for DX
                                                        // However on GL layout is VAO bound, so another separate call is needed for GL

    auto anotherVA = LzUniPtr<Lafez::VertexArray>{ Lafez::RendererBackend::genVertexArray() };
    auto anotherAB = LzShrPtr<Lafez::ArrayBuffer>{ Lafez::RendererBackend::genArrayBuffer(anotherData, sizeof(float) * 18, 3) };
    anotherVA->addIndexBuffer(indexBuffer);
    anotherVA->addArrayBuffer(anotherAB);
    anotherAB->setBufferLayout(layout, shader.get());

    while (Lafez::Window::update()) {
        static auto spice = .0f;
        Lafez::RendererBackend::clearBuffer(std::sinf(spice), 1.0f, std::cosf(spice), 1.0f);
        Lafez::RendererBackend::drawVertexArray(*vertexArray);
        Lafez::RendererBackend::drawVertexArray(*anotherVA);
        mLayerStack.update();

        // Render shits
        Lafez::RendererBackend::swapBuffers();
        spice += .01f;
    }
}

void ExampleApplication::shutDown() {
	mLayerStack.flush();
	Lafez::shutDown();
}

Lafez::Application* Lafez::createApplication() {
    return new ExampleApplication;
}