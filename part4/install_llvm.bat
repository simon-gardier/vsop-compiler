@echo off
echo VSOP Compiler - LLVM Installation Helper for Windows
echo ====================================================
echo.

echo Checking for existing LLVM installation...
where llvm-config >nul 2>&1
if %errorlevel% equ 0 (
    echo Found existing LLVM installation:
    llvm-config --version
    echo.
    echo LLVM is already installed. You can proceed with building.
    goto :end
)

echo LLVM not found. Please install LLVM manually:
echo.
echo 1. Download LLVM from: https://releases.llvm.org/
echo    - Choose the latest stable release
echo    - Download the Windows installer (.exe)
echo.
echo 2. Run the installer:
echo    - Choose "Add LLVM to the system PATH for all users"
echo    - Install to default location (usually C:\Program Files\LLVM)
echo.
echo 3. Restart your command prompt/terminal
echo.
echo 4. Verify installation by running: llvm-config --version
echo.
echo Alternative: Use Chocolatey package manager:
echo   choco install llvm
echo.
echo Alternative: Use MSYS2:
echo   pacman -S mingw-w64-x86_64-llvm
echo.

:end
echo.
echo After installing LLVM, you can build the compiler with:
echo   make clean
echo   make
echo.
pause
