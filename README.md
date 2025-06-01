# Terminal Chess Game

A two-player chess game that runs in the terminal, written in C++ with a clean, modular architecture.

## Features

- Full chess board with all pieces
- Complete move validation for all piece types
- Check and checkmate detection
- Turn-based gameplay
- Intuitive coordinate-based move input (e.g., A2->A3)
- Helpful error messages for invalid moves
- Clean terminal display with ASCII board
- **Modular, well-organized codebase** for easy maintenance and extension

## Project Structure

The codebase has been refactored for better organization and maintainability:

```
├── include/                 # Header files
│   ├── types.h             # Core types and enums
│   ├── move.h              # Move class
│   ├── move_parser.h       # Move parsing utilities
│   ├── piece.h             # Base piece class
│   ├── sliding_piece.h     # Base class for sliding pieces
│   ├── path_validator.h    # Path validation utilities
│   ├── chessboard.h        # Chess board class
│   ├── game_state.h        # Game state management
│   ├── board_renderer.h    # Display logic
│   ├── move_validator.h    # Move validation logic
│   ├── chess_game.h        # Main game class
│   └── pieces/             # Individual piece classes
│       ├── pawn.h
│       ├── rook.h
│       ├── knight.h
│       ├── bishop.h
│       ├── queen.h
│       └── king.h
├── src/                    # Source files
│   ├── utils/              # Utility classes
│   ├── pieces/             # Piece implementations
│   ├── board/              # Board-related classes
│   └── game/               # Game logic classes
├── main.cpp                # Entry point
└── Makefile               # Build configuration
```

## Architecture Improvements

The refactored codebase provides several benefits:

### 1. **Separation of Concerns**
- **Move parsing** is handled by `MoveParser` class
- **Move validation** is centralized in `MoveValidator` class
- **Display logic** is separated in `BoardRenderer` class
- **Game state** is managed by `GameState` class

### 2. **Reduced Code Duplication**
- `SlidingPiece` base class eliminates duplication between Rook, Bishop, and Queen
- `PathValidator` centralizes path-checking logic
- Common movement patterns are reused across pieces

### 3. **Better Testability**
- Each class has a single responsibility
- Dependencies are clearly defined
- Logic is separated from I/O operations

### 4. **Easier Navigation**
- Related functionality is grouped in logical directories
- Header files clearly define interfaces
- Implementation details are separated from declarations

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

## Error Messages

The game provides helpful error messages for:
- Invalid move format
- Invalid coordinates
- No piece at source position
- Moving opponent's piece
- Capturing your own piece
- Invalid moves for specific piece types
- Moves that would result in check

## Development

### Adding New Features

The modular structure makes it easy to extend the game:

- **New piece types**: Inherit from `Piece` or `SlidingPiece`
- **New move types**: Extend the `MoveType` enum and update `MoveValidator`
- **New display options**: Modify `BoardRenderer` class
- **New game modes**: Extend `GameState` class

### Code Quality

The refactored codebase follows modern C++ best practices:
- RAII for resource management
- Smart pointers for memory safety
- Const-correctness
- Clear separation of interface and implementation
- Minimal dependencies between classes

## Testing

The game has been successfully compiled and tested with the new architecture. You should see:
- A welcome message and instructions
- A properly formatted chess board with pieces in starting positions
- Responsive input handling for moves and commands
- Clear error messages for invalid moves

The modular structure also makes unit testing much easier, as each component can be tested independently.

Enjoy your game of chess! 