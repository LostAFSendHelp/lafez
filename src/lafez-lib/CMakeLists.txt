include(GenerateExportHeader)

add_library(
    lafez-lib SHARED

    lafez/utils/Log.hpp
    lafez/utils/Log.cpp

    lafez/core/lafez_event.hpp
    lafez/core/lafez_layer.hpp
    lafez/core/lafez_window.hpp
    
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

    lafez/core/window/Window.hpp
    lafez/core/window/Window.cpp

    lafez/core/window/platforms/win/WinWindow.hpp
    lafez/core/window/platforms/win/WinWindow.cpp

    lafez/core/layers/Layer.hpp
    lafez/core/layers/Layer.cpp
    lafez/core/layers/LayerStack.hpp
    lafez/core/layers/LayerStack.cpp
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
    glad
    glfw
)

target_include_directories(
    lafez-lib

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/exports
)
