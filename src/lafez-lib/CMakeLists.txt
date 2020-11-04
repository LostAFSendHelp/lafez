include(GenerateExportHeader)

add_library(
    lafez-lib SHARED

    lafez/lafez.hpp
    lafez/lafez.cpp

    lafez/utils/log.hpp
    lafez/utils/log.cpp
)

generate_export_header(
    lafez-lib
    BASE_NAME LAFEZLIB
    EXPORT_MACRO_NAME LAFEZLIB
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/exports/lafezlib_export.h
)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(lafez-lib PUBLIC spdlog::spdlog)
target_include_directories(lafez-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/exports)
