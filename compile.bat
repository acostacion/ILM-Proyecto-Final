@echo off
echo.
echo =====================================
echo   Compilador SCons - Godot 4D
echo =====================================
echo.

echo [1/2] Limpiando...
scons -c

echo.
echo [2/2] Compilando...

:: Compilacion para Windows x86_64, con target template_debug y template_release
scons platform=windows arch=x86_64 target=template_debug -j8
scons platform=windows arch=x86_64 target=template_release -j8


if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR
    pause
    exit /b 1
)

echo.
echo =====================================
echo   COMPILADO CON EXITO
echo =====================================
echo.