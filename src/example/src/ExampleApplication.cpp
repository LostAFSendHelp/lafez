#include "ExampleApplication.hpp"
#include <lafez/core/lafez_gfx.hpp>
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
    auto shader = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genDefaultShader() };

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

    Lafez::VertexAttribute attribs[] = {
        { "VS_POSITION", LZ_PTYPE_VEC3F },
        { "VS_COLOR", LZ_PTYPE_VEC3F }
    };

    uint32_t indices[] = { 0, 1, 2 };

    auto vertexBuffer = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genVertexBuffer(data, sizeof(float) * 18, 3) };
    auto indexBuffer = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genIndexBuffer(indices, 3) };
    auto vbLayout = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genVBLayout(attribs, 2, shader.get()) };
    Lafez::Drawable drawable{ Lafez::Gfx::gfx() };
    drawable.addBindable(vertexBuffer);
    drawable.addBindable(vbLayout);
    drawable.addBindable(indexBuffer);
    drawable.addBindable(shader);
    
    auto anotherVB = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genVertexBuffer(anotherData, sizeof(float) * 18, 3) };
    auto anotherIB = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genIndexBuffer(indices, 3) };
    auto anotherVBLayout = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genVBLayout(attribs, 2, shader.get()) };
    Lafez::Drawable anotherDrawable{ Lafez::Gfx::gfx() };
    anotherDrawable.addBindable(anotherVB);
    anotherDrawable.addBindable(anotherVBLayout);
    anotherDrawable.addBindable(anotherIB);
    anotherDrawable.addBindable(shader);

    while (Lafez::Window::update()) {
        static auto spice = .0f;
        Lafez::Gfx::gfx()->clearBuffer(std::sinf(spice), 1.0f, std::cosf(spice), 1.0f);
        drawable.draw();
        anotherDrawable.draw();
        mLayerStack.update();

        // Render shits
        Lafez::Gfx::gfx()->swapBuffers();
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