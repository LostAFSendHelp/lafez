@echo off
set config=%1

if %config% == r (
    echo BUILDING USING [RELEASE] CONFIGURATION
    cmake --build build --config Release
    goto:eof
)

if %config% == d (
    echo BUILDING USING [DEBUG] CONFIGURATION
    cmake --build build --config Debug
    goto:eof
)

if %config% == rdb (
    echo BUILDING USING [RELWITHDEBINFO] CONFIGURATION
    cmake --build build --config RelWithDebInfo
    goto:eof
)

echo BUILD OPTION NOT RECOGNIZED. BUILDING USING DEFAULT CONFIGURATION
cmake --build build
