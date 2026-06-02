@echo off
echo =====================================
echo  Compilador SCons - Godot 4D (WEB)
echo =====================================
echo.

:: Emscripten debe estar activado en esta terminal.
:: Si emcc no esta en el PATH, descomenta y ajusta la ruta:
call C:\emsdk\emsdk_env.bat

echo [1/2] Compilando web template_debug...
scons platform=web target=template_debug threads=no -j8
if %ERRORLEVEL% neq 0 goto :error
echo.
echo [2/2] Compilando web template_release...
scons platform=web target=template_release threads=no -j8
if %ERRORLEVEL% neq 0 goto :error

echo.
echo =====================================
echo  COMPILADO CON EXITO (WEB)
echo =====================================
echo.
pause
exit /b 0

:error
echo.
echo =====================================
echo  ERROR EN LA COMPILACION
echo =====================================
echo.
pause
exit /b 1
