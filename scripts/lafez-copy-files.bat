@echo off

echo ----------------------------------------------
echo [LAFEZ-LIB BUILD SUCCESS, COPYING ASSET FILES]
robocopy src\lafez-lib\assets\renderer\shaders %1\assets\shaders /E >nul

exit 0