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
:: Para compilar mas específicamente, usar:
:: scons platform=windows arch=x86_64 target=template_debug -j8
scons platform=windows

if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR
    pause
    exit /b 1
)

echo.
echo =====================================
echo   ¡COMPILADO!
echo =====================================
echo.
pause