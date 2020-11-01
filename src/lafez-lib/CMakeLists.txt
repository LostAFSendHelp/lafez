include(GenerateExportHeader)

add_library(
    lafez-lib SHARED

    src/lafez.hpp
    src/lafez.cpp

    src/utils/log.hpp
    src/utils/log.cpp
)

generate_export_header(
    lafez-lib
    BASE_NAME LAFEZLIB
    EXPORT_MACRO_NAME LAFEZLIB
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/exports/lafezlib_export.h
)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(lafez-lib PUBLIC spdlog::spdlog)
target_include_directories(lafez-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/exports)
