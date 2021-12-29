#include "ExampleApplication.hpp"
#include <lafez/core/lafez_gfx.hpp>
#include <lafez/core/lafez_asset.hpp>
#include <lafez/core/lafez_event.hpp>
#include <lafez/Lafez.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    float cube[] = {
         1.0f,  1.0f, -1.0f, 1.0f,  .0f,  .0f,
        -1.0f,  1.0f, -1.0f, 1.0f,  .0f,  .0f,
        -1.0f,  1.0f,  1.0f, 1.0f,  .0f,  .0f,
         1.0f,  1.0f,  1.0f, 1.0f,  .0f,  .0f,
         1.0f, -1.0f, -1.0f,  .0f, 1.0f,  .0f,
        -1.0f, -1.0f, -1.0f,  .0f,  .0f, 1.0f,
        -1.0f, -1.0f,  1.0f,  .0f, 1.0f,  .0f,
         1.0f, -1.0f,  1.0f,  .0f,  .0f, 1.0f,
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3,

        0, 4, 5,
        0, 5, 1,

        1, 5, 6,
        1, 6, 2,

        2, 6, 7,
        2, 7, 3,

        3, 7, 4,
        3, 4, 0,

        4, 7, 6,
        4, 6, 5
    };

    Lafez::VertexAttribute attribs[] = {
        { "VS_POSITION", LZ_PTYPE_VEC3F },
        { "VS_COLOR", LZ_PTYPE_VEC3F }
    };

    LzVec<LzUniPtr<Lafez::Drawable>> drawables;
    drawables.reserve(4);
    for (unsigned int index = 0; index < 4; ++index) {
        auto vertexBuffer = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genVertexBuffer(cube, sizeof(float) * 6 * 8, 8) };
        auto vbLayout = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genVBLayout(attribs, 2, shader.get()) };
        auto indexBuffer = LzShrPtr<Lafez::Bindable>{ Lafez::Gfx::gfx()->genIndexBuffer(indices, 36) };
        drawables.emplace_back(new Lafez::Drawable{ Lafez::Gfx::gfx() });
        drawables[index]->addBindable(vertexBuffer);
        drawables[index]->addBindable(indexBuffer);
        drawables[index]->addBindable(vbLayout);
        drawables[index]->addBindable(shader);
        drawables[index]->transform.scale(.2f);
    }

    auto magnitude = 2.0f;
    drawables[0]->transform.translate({ magnitude, .0f, .0f });
    drawables[1]->transform.translate({ .0f, magnitude, .0f });
    drawables[2]->transform.translate({ .0f, .0f, magnitude });

    auto radians = .05f;
    glm::vec3 axis { 1.0f, .0f, .0f };

    glm::vec3 position{ 1.f, 3.0f, 5.0f };
    glm::vec3 up{ .0f, 1.0f, .0f };
    glm::vec3 center{ .0f, .0f, .0f };

    Lafez::Gfx::gfx()->setView(glm::lookAt(position, center, up));
    Lafez::Gfx::gfx()->setProjection(glm::perspective(45.0f, 1280.0f / 768.0f, .1f, 100.0f));

    while (Lafez::Window::update()) {
        static auto spice = .0f;
        Lafez::Gfx::gfx()->clearBuffer(.0f, .0f, .0f, 1.0f);
        for (const auto& drawable : drawables) {
            drawable->draw();
            //drawable->transform.rotate(radians, axis);
        }
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
