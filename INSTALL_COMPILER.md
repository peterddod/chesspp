# Installing a C++ Compiler on Windows

To compile and run the chess game, you need a C++ compiler. Here are the easiest options:

## Option 1: MinGW-w64 (Recommended for beginners)

1. **Download MSYS2**:
   - Go to https://www.msys2.org/
   - Download the installer and run it
   - Follow the installation instructions

2. **Install MinGW-w64**:
   - Open MSYS2 terminal
   - Run: `pacman -S mingw-w64-x86_64-gcc`
   - Add `C:\msys64\mingw64\bin` to your Windows PATH environment variable

3. **Verify installation**:
   - Open Command Prompt or PowerShell
   - Run: `g++ --version`

## Option 2: Microsoft Visual Studio Build Tools

1. **Download Visual Studio Installer**:
   - Go to https://visualstudio.microsoft.com/downloads/
   - Download "Build Tools for Visual Studio"

2. **Install C++ Build Tools**:
   - Run the installer
   - Select "C++ build tools" workload
   - Install

3. **Use Developer Command Prompt**:
   - Search for "Developer Command Prompt" in Start Menu
   - Use `cl` command to compile

## Option 3: LLVM/Clang

1. **Download LLVM**:
   - Go to https://releases.llvm.org/
   - Download the Windows installer
   - Make sure to add LLVM to PATH during installation

2. **Verify installation**:
   - Open Command Prompt or PowerShell
   - Run: `clang++ --version`

## After Installation

1. Navigate to the chess game directory
2. Run `.\compile.bat` - it will automatically detect your compiler
3. Run `chess.exe` to play the game!

## Alternative: Online Compilers

If you don't want to install a compiler locally, you can use online C++ compilers:

1. Copy all the code files (chess.h, chess.cpp, main.cpp) to an online compiler like:
   - https://replit.com/
   - https://onlinegdb.com/
   - https://www.programiz.com/cpp-programming/online-compiler/

2. Compile and run online

Note: Online compilers may have limitations with terminal input/output formatting. 