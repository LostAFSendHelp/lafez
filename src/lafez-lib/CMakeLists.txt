include(GenerateExportHeader)

add_library(
    lafez-lib SHARED

    lafez/Application.hpp
    lafez/Application.cpp
    lafez/Lafez.hpp

    lafez/utils/Log.hpp
    lafez/utils/Log.cpp

    lafez/core/lafez_asset.hpp
    lafez/core/lafez_event.hpp
    lafez/core/lafez_foundation.hpp
    lafez/core/lafez_layer.hpp
    lafez/core/lafez_gfx.hpp
    
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
    lafez/core/foundation/Key.hpp
    lafez/core/foundation/Key.cpp

    lafez/core/foundation/platforms/gl/GlWindow.hpp
    lafez/core/foundation/platforms/gl/GlWindow.cpp
    lafez/core/foundation/platforms/gl/GlImGui.hpp
    lafez/core/foundation/platforms/gl/GlImGui.cpp
    lafez/core/foundation/platforms/gl/GlInput.hpp
    lafez/core/foundation/platforms/gl/GlInput.cpp

    lafez/core/foundation/platforms/dx/DxWindow.hpp 
    lafez/core/foundation/platforms/dx/DxWindow.cpp
    lafez/core/foundation/platforms/dx/DxImGui.hpp
    lafez/core/foundation/platforms/dx/DxImGui.cpp
    
    lafez/core/layers/Layer.hpp
    lafez/core/layers/Layer.cpp
    lafez/core/layers/LayerStack.hpp
    lafez/core/layers/LayerStack.cpp

    lafez/core/layers/impl/ImGuiLayer.hpp
    lafez/core/layers/impl/ImGuiLayer.cpp

    lafez/core/graphics/Gfx.hpp
    lafez/core/graphics/Gfx.cpp
    lafez/core/graphics/Bindable.hpp
    lafez/core/graphics/Bindable.cpp
    lafez/core/graphics/Drawable.hpp
    lafez/core/graphics/Drawable.cpp
    lafez/core/graphics/VertexAttribute.hpp
    lafez/core/graphics/VertexAttribute.cpp
    lafez/core/graphics/Transform.hpp
    lafez/core/graphics/Transform.cpp
    lafez/core/graphics/CBuffer.hpp
    
    lafez/core/graphics/platforms/dx/DxGfx.hpp
    lafez/core/graphics/platforms/dx/DxGfx.cpp
    lafez/core/graphics/platforms/dx/DxShader.hpp
    lafez/core/graphics/platforms/dx/DxShader.cpp
    lafez/core/graphics/platforms/dx/DxBuffer.hpp
    lafez/core/graphics/platforms/dx/DxBuffer.cpp
    
    

    lafez/core/graphics/platforms/gl/GlGfx.hpp
    lafez/core/graphics/platforms/gl/GlGfx.cpp
    lafez/core/graphics/platforms/gl/GlShader.hpp
    lafez/core/graphics/platforms/gl/GlShader.cpp
    lafez/core/graphics/platforms/gl/GlBuffer.hpp
    lafez/core/graphics/platforms/gl/GlBuffer.cpp
    
    
    

    lafez/core/assets/Asset.hpp
    lafez/core/assets/Asset.cpp
    lafez/core/foundation/WindowInfo.cpp
    lafez/core/foundation/WindowInfo.hpp

    lafez/misc/lafez_exception.hpp
    lafez/misc/Exception.hpp
    lafez/misc/Exception.cpp
    lafez/misc/BadFileException.hpp
    lafez/misc/BadFileException.cpp
    lafez/misc/RuntimeException.hpp
    lafez/misc/RuntimeException.cpp

    lafez/misc/platforms/WinException.hpp
    lafez/misc/platforms/WinException.cpp
    lafez/misc/platforms/GlException.cpp
    lafez/misc/platforms/GlException.cpp

    lafez/platform_headers/lafez_gl.hpp
)

target_precompile_headers(
    lafez-lib
    
    PRIVATE
    lafez/lafez_pch.hpp
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
    glm
    lafez-imgui # strip this from client side for release build
    
    PRIVATE
    glad
    glfw
    nlohmann_json
)

target_include_directories(
    lafez-lib

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/exports
)

set(LAFEZ_ASSET_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets PARENT_SCOPE)