# Terminal Chess Game

A two-player chess game that runs in the terminal, written in C++ with a clean, modular architecture featuring a **separated chess engine and user interface**.

## Features

- Full chess board with all pieces
- Complete move validation for all piece types
- Check and checkmate detection
- Turn-based gameplay
- Intuitive coordinate-based move input (e.g., A2->A3)
- Helpful error messages for invalid moves
- Clean terminal display with ASCII board
- **Separated chess engine from UI** for easy integration and testing
- **Modular, well-organized codebase** for easy maintenance and extension

## Architecture Overview

The codebase has been designed with a **clear separation between the chess engine and the user interface**:

### **ChessPP** - Pure Chess Engine
- **Independent chess engine** with no UI dependencies
- Clean API for move execution and game state queries
- Comprehensive move validation and game logic
- Can be easily integrated into different UIs (terminal, GUI, web, etc.)

### **CommandLineDisplay** - Terminal Interface
- Handles all terminal input/output
- Uses ChessPP as the underlying chess engine
- Manages user interaction and display formatting
- Complete separation from engine logic

## Project Structure

```
├── include/                 # Header files
│   ├── chesspp.h           # Chess engine class
│   ├── command_line_display.h # Terminal interface class
│   ├── types.h             # Core types and enums
│   ├── move.h              # Move class
│   ├── move_parser.h       # Move parsing utilities
│   ├── piece.h             # Base piece class
│   ├── sliding_piece.h     # Base class for sliding pieces
│   ├── path_validator.h    # Path validation utilities
│   ├── chessboard.h        # Chess board class
│   ├── game_state.h        # Game state management
│   ├── move_validator.h    # Move validation logic
│   └── pieces/             # Individual piece classes
│       ├── pawn.h
│       ├── rook.h
│       ├── knight.h
│       ├── bishop.h
│       ├── queen.h
│       └── king.h
├── src/                    # Source files
│   ├── game/              # Chess engine implementation
│   │   ├── chesspp.cpp    # Main chess engine
│   │   └── game_state.cpp # Game state management
│   ├── ui/                # User interface implementations
│   │   └── command_line_display.cpp # Terminal interface
│   ├── utils/             # Utility classes
│   ├── pieces/            # Piece implementations
│   └── board/             # Board-related classes
├── main.cpp               # Entry point (uses CommandLineDisplay)
└── Makefile              # Build configuration
```

## Architecture Benefits

### 1. **Clean Separation of Concerns**
- **ChessPP**: Pure chess logic, no UI dependencies
- **CommandLineDisplay**: UI handling, uses ChessPP as engine
- Easy to create alternative interfaces (GUI, web, mobile)

### 2. **Engine Reusability**
- ChessPP can be used in any application
- Perfect for AI development, analysis tools, or different UIs
- Comprehensive API for all chess operations

### 3. **Easy Testing**
- Engine logic can be tested independently
- UI behavior can be tested separately
- Clear interfaces make unit testing straightforward

### 4. **Extensibility**
- Add new UI types without touching engine code
- Enhance engine features without affecting existing UIs
- Plugin-style architecture for different interfaces

## ChessPP Engine API

The chess engine provides a clean, comprehensive API:

```cpp
class ChessPP {
public:
    // Core functionality
    MoveResult makeMove(const std::string& moveStr);
    MoveResult makeMove(const Move& move);
    
    // Game state queries
    GameStatus getGameStatus() const;
    Color getCurrentPlayer() const;
    bool isGameOver() const;
    
    // Board access
    const ChessBoard& getBoard() const;
    const Piece* getPieceAt(const Position& pos) const;
    
    // Move validation
    bool isValidMove(const std::string& moveStr) const;
    std::vector<Move> getPossibleMoves() const;
    
    // Game control
    void resetGame();
    void endGame(const std::string& result);
};
```

## Compilation

### Windows
**Note**: You need a C++ compiler installed. If you don't have one, see [INSTALL_COMPILER.md](INSTALL_COMPILER.md) for installation instructions.

1. **Using the provided batch file (Recommended)**:
   ```cmd
   .\compile.bat
   ```
   This will automatically detect and use an available C++ compiler.

2. **Manual compilation** (if you have a C++ compiler installed):
   - **MinGW/g++**: `g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/**/*.cpp -o chess.exe`
   - **Clang**: `clang++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/**/*.cpp -o chess.exe`

### Linux/macOS
1. **Using Make (Recommended)**:
   ```bash
   make
   ```

2. **Manual compilation**:
   ```bash
   g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/**/*.cpp -o chess
   ```

## How to Play

1. Run the game:
   - **Windows**: `chess.exe`
   - **Linux/macOS**: `./chess`

2. Enter moves in one of these formats:
   - `A2->A3` (with arrow)
   - `A2-A3` (with dash)
   - `A2 A3` (with space)

3. Coordinates:
   - Columns: A-H (left to right)
   - Rows: 1-8 (bottom to top)
   - White pieces start at rows 1-2
   - Black pieces start at rows 7-8

4. Piece symbols:
   - **White pieces (uppercase)**: P=Pawn, R=Rook, N=Knight, B=Bishop, Q=Queen, K=King
   - **Black pieces (lowercase)**: p=pawn, r=rook, n=knight, b=bishop, q=queen, k=king

5. Special commands:
   - `help` - Show help message
   - `quit` or `exit` - Exit the game

## Game Rules

- White always moves first
- Standard chess rules apply for all pieces
- The game detects check and checkmate automatically
- You cannot make moves that would put your own king in check
- The game ends when checkmate is achieved

## Example Moves

- `E2->E4` - Move white pawn from E2 to E4
- `G8-F6` - Move black knight from G8 to F6
- `D1 H5` - Move white queen from D1 to H5

## Development

### Using ChessPP in Your Own Projects

The ChessPP engine can be easily integrated into your own applications:

```cpp
#include "chesspp.h"

int main() {
    ChessPP engine;
    
    // Make moves
    MoveResult result = engine.makeMove("E2->E4");
    if (result == MoveResult::SUCCESS) {
        // Move was successful
        std::cout << "Current player: " << (engine.getCurrentPlayer() == Color::WHITE ? "White" : "Black") << std::endl;
    }
    
    // Check game status
    GameStatus status = engine.getGameStatus();
    if (status == GameStatus::CHECK) {
        std::cout << "King is in check!" << std::endl;
    }
    
    return 0;
}
```

### Creating Alternative UIs

To create a new interface (GUI, web, etc.), simply:
1. Include `chesspp.h`
2. Create an instance of `ChessPP`
3. Use the engine's API for all chess operations
4. Handle display and input in your preferred framework

### Code Quality

The refactored codebase follows modern C++ best practices:
- RAII for resource management
- Smart pointers for memory safety
- Const-correctness
- Clear separation of interface and implementation
- Minimal dependencies between classes
- **Zero coupling between engine and UI**

Enjoy your game of chess! 