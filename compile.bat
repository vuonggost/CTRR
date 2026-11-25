@echo off
echo ===============================================
echo   COMPILING SMART PARKING SYSTEM
echo ===============================================
echo.

REM Compile main.cpp with UI
g++ -o smart_parking main.cpp -std=c++11

IF %ERRORLEVEL% EQU 0 (
    echo.
    echo ✓ Compilation successful!
    echo.
    echo Running Smart Parking System...
    echo ===============================================
    smart_parking
) ELSE (
    echo.
    echo ✗ Compilation failed!
    echo Please check the errors above.
    pause
)
