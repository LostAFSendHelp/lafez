include(GenerateExportHeader)

add_library(
    lafez-lib SHARED

    lafez/utils/Log.hpp
    lafez/utils/Log.cpp

    lafez/core/lafez_event.hpp
    lafez/core/lafez_window.hpp
    
    lafez/core/event/Event.hpp
    lafez/core/event/Event.cpp

    lafez/core/event/MouseButtonEvent.hpp
    lafez/core/event/MouseButtonEvent.cpp
    lafez/core/event/MouseMoveEvent.hpp
    lafez/core/event/MouseMoveEvent.cpp
    
    lafez/core/event/KeyEvent.hpp
    lafez/core/event/KeyEvent.cpp
    
    lafez/core/event/WindowCloseEvent.hpp
    lafez/core/event/WindowCloseEvent.cpp
    lafez/core/event/WindowResizeEvent.hpp
    lafez/core/event/WindowResizeEvent.cpp
    
    lafez/core/event/EventCenter.hpp
    lafez/core/event/EventCenter.cpp
    lafez/core/event/EventSubscription.hpp
    lafez/core/event/EventSubscription.cpp
    lafez/core/event/DisposeBag.hpp
    lafez/core/event/DisposeBag.cpp

    lafez/core/window/Window.hpp
    lafez/core/window/Window.cpp

    lafez/core/window/platforms/win/WinWindow.hpp
    lafez/core/window/platforms/win/WinWindow.cpp
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

find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(
    lafez-lib

    PUBLIC
    spdlog::spdlog
    glfw
)

target_include_directories(
    lafez-lib

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/exports
)
