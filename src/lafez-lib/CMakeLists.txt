include(GenerateExportHeader)

add_library(
    lafez-lib SHARED

    lafez/utils/Log.hpp
    lafez/utils/Log.cpp

    lafez/core/lafe_event.hpp
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

find_package(spdlog CONFIG REQUIRED)

target_link_libraries(
    lafez-lib

    PUBLIC
    spdlog::spdlog
)

target_include_directories(
    lafez-lib

    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/exports
)
