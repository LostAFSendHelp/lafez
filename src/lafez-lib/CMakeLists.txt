include(GenerateExportHeader)

add_library(
    lafez-lib SHARED

    lafez/utils/Log.hpp
    lafez/utils/Log.cpp

    lafez/core/lafez_asset.hpp
    lafez/core/lafez_event.hpp
    lafez/core/lafez_foundation.hpp
    lafez/core/lafez_layer.hpp
    lafez/core/lafez_renderer.hpp
    
    lafez/core/event/data/Event.hpp
    lafez/core/event/data/Event.cpp

    lafez/core/event/data/MouseButtonEvent.hpp
    lafez/core/event/data/MouseButtonEvent.cpp
    lafez/core/event/data/MouseMoveEvent.hpp
    lafez/core/event/data/MouseMoveEvent.cpp
    lafez/core/event/data/MouseScrollEvent.hpp
    lafez/core/event/data/MouseScrollEvent.cpp
    
    lafez/core/event/data/KeyEvent.hpp
    lafez/core/event/data/KeyEvent.cpp
    
    lafez/core/event/data/WindowCloseEvent.hpp
    lafez/core/event/data/WindowCloseEvent.cpp
    lafez/core/event/data/WindowResizeEvent.hpp
    lafez/core/event/data/WindowResizeEvent.cpp
    
    lafez/core/event/control/EventCenter.hpp
    lafez/core/event/control/EventCenter.cpp
    lafez/core/event/control/EventSubscription.hpp
    lafez/core/event/control/EventSubscription.cpp
    lafez/core/event/control/DisposeBag.hpp
    lafez/core/event/control/DisposeBag.cpp

    lafez/core/foundation/Foundation.hpp
    lafez/core/foundation/Foundation.cpp

    lafez/core/foundation/Window.hpp
    lafez/core/foundation/Window.cpp
    lafez/core/foundation/Input.hpp
    lafez/core/foundation/Input.cpp
    lafez/core/foundation/ImGuiBackend.hpp
    lafez/core/foundation/ImGuiBackend.cpp

    lafez/core/foundation/platforms/gl/GlWindow.hpp
    lafez/core/foundation/platforms/gl/GlWindow.cpp
    lafez/core/foundation/platforms/gl/GlImGui.hpp
    lafez/core/foundation/platforms/gl/GlImGui.cpp
    lafez/core/foundation/platforms/gl/GlInput.hpp
    lafez/core/foundation/platforms/gl/GlInput.cpp

    lafez/core/layers/Layer.hpp
    lafez/core/layers/Layer.cpp
    lafez/core/layers/LayerStack.hpp
    lafez/core/layers/LayerStack.cpp

    lafez/core/layers/impl/ImGuiLayer.hpp
    lafez/core/layers/impl/ImGuiLayer.cpp

    lafez/core/renderer/Buffer.hpp
    lafez/core/renderer/Buffer.cpp
    lafez/core/renderer/RendererBackend.hpp
    lafez/core/renderer/RendererBackend.cpp
    lafez/core/renderer/Shader.hpp
    lafez/core/renderer/Shader.cpp
    lafez/core/renderer/VertexArray.hpp
    lafez/core/renderer/VertexArray.cpp

    lafez/core/renderer/platforms/GlRenderer.hpp
    lafez/core/renderer/platforms/GlRenderer.cpp
    lafez/core/renderer/platforms/DxRenderer.hpp
    lafez/core/renderer/platforms/DxRenderer.cpp
    lafez/core/renderer/platforms/VkRenderer.hpp
    lafez/core/renderer/platforms/VkRenderer.cpp

    lafez/core/assets/Asset.hpp
    lafez/core/assets/Asset.cpp
)

set_target_properties(
    lafez-lib

    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_precompile_headers(
    lafez-lib
    
    PRIVATE
    lafez/lafez_pch.hpp
)

add_compile_definitions(
    $<$<PLATFORM_ID:Windows>:__LZ_WIN>
    $<$<PLATFORM_ID:Darwin>:__LZ_MAC>
    $<$<PLATFORM_ID:Linux>:__LZ_LNX>
)

generate_export_header(
    lafez-lib

    BASE_NAME LAFEZLIB
    EXPORT_MACRO_NAME LAFEZLIB
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/exports/lafezlib_export.h
)

target_link_libraries(
    lafez-lib

    PUBLIC
    spdlog::spdlog
    lafez-imgui # strip this from client side for release build
    
    PRIVATE
    glad
    glfw
)

target_include_directories(
    lafez-lib

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/exports
)
