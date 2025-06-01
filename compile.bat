@echo off
echo Compiling Chess Game...

REM Define source files
set SOURCES=main.cpp src/utils/move.cpp src/utils/move_parser.cpp src/utils/path_validator.cpp src/utils/move_validator.cpp src/pieces/sliding_piece.cpp src/pieces/pawn.cpp src/pieces/rook.cpp src/pieces/knight.cpp src/pieces/bishop.cpp src/pieces/queen.cpp src/pieces/king.cpp src/board/chessboard.cpp src/game/game_state.cpp src/game/chesspp.cpp src/ui/command_line_display.cpp

REM Try g++ first (MinGW)
where g++ >nul 2>&1
if %errorlevel% == 0 (
    echo Using g++...
    g++ -std=c++17 -Wall -Wextra -Iinclude %SOURCES% -o chess.exe
    if %errorlevel% == 0 (
        echo Compilation successful! Run chess.exe to play.
        goto :end
    )
)

REM Try clang++
where clang++ >nul 2>&1
if %errorlevel% == 0 (
    echo Using clang++...
    clang++ -std=c++17 -Wall -Wextra -Iinclude %SOURCES% -o chess.exe
    if %errorlevel% == 0 (
        echo Compilation successful! Run chess.exe to play.
        goto :end
    )
)

REM Try Microsoft Visual C++ (cl)
where cl >nul 2>&1
if %errorlevel% == 0 (
    echo Using Microsoft Visual C++...
    cl /EHsc /std:c++17 /I include %SOURCES% /Fe:chess.exe
    if %errorlevel% == 0 (
        echo Compilation successful! Run chess.exe to play.
        goto :end
    )
)

echo Error: No C++ compiler found!
echo Please install one of the following:
echo - MinGW-w64 (includes g++)
echo - LLVM/Clang
echo - Microsoft Visual Studio Build Tools
echo.
echo Or compile manually if you have a C++ compiler installed.

:end
pause 