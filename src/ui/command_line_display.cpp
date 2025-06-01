#include "../../include/command_line_display.h"
#include <iostream>

void CommandLineDisplay::play() {
    displayWelcome();
    
    while (!engine.isGameOver()) {
        displayBoard();
        displayGameStatus();
        
        std::cout << "Enter your move (or 'quit' to exit, 'help' for help): ";
        std::string input;
        std::getline(std::cin, input);
        
        if (handleUserInput(input)) {
            continue;
        }
        
        std::cout << "\n";
    }
    
    displayGameResult();
}

void CommandLineDisplay::displayBoard() {
    std::cout << "\n";
    displayRowSeparator();
    
    for (int i = 0; i < ChessBoard::BOARD_SIZE; i++) {
        std::cout << (ChessBoard::BOARD_SIZE - i) << " |";
        for (int j = 0; j < ChessBoard::BOARD_SIZE; j++) {
            const Piece* piece = engine.getPieceAt(Position(i, j));
            if (piece) {
                std::cout << " " << piece->getSymbol() << " |";
            } else {
                std::cout << "   |";
            }
        }
        std::cout << "\n";
        displayRowSeparator();
    }
    
    displayColumnHeaders();
    displayCurrentPlayer();
    
    std::cout << "Legend: Uppercase = White pieces, Lowercase = Black pieces\n";
    std::cout << "P/p = Pawn, R/r = Rook, N/n = Knight, B/b = Bishop, Q/q = Queen, K/k = King\n\n";
}

void CommandLineDisplay::displayWelcome() {
    std::cout << "========================================\n";
    std::cout << "         Welcome to Chess Game!        \n";
    std::cout << "========================================\n\n";
    std::cout << "This is a two-player chess game.\n";
    std::cout << "White pieces are represented by uppercase letters.\n";
    std::cout << "Black pieces are represented by lowercase letters.\n\n";
    displayHelp();
}

void CommandLineDisplay::displayHelp() {
    std::cout << "How to play:\n";
    std::cout << "- Enter moves in the format: A2->A3 or A2-A3 or A2 A3\n";
    std::cout << "- Columns are labeled A-H, rows are labeled 1-8\n";
    std::cout << "- White starts first\n";
    std::cout << "- Type 'quit' to exit the game\n";
    std::cout << "- Type 'help' to see this message again\n\n";
}

void CommandLineDisplay::displayGameResult() {
    std::cout << "\n========================================\n";
    std::cout << "                GAME OVER               \n";
    std::cout << "========================================\n";
    std::cout << engine.getGameResult() << "\n";
    std::cout << "========================================\n\n";
}

void CommandLineDisplay::displayCurrentPlayer() {
    std::cout << "Current player: " << colorToString(engine.getCurrentPlayer()) << "\n";
}

void CommandLineDisplay::displayColumnHeaders() {
    std::cout << "    A   B   C   D   E   F   G   H\n\n";
}

void CommandLineDisplay::displayRowSeparator() {
    std::cout << "  +---+---+---+---+---+---+---+---+\n";
}

void CommandLineDisplay::displayGameStatus() {
    GameStatus status = engine.getGameStatus();
    if (status == GameStatus::CHECK) {
        std::cout << colorToString(engine.getCurrentPlayer()) << " is in check!\n";
    }
}

bool CommandLineDisplay::handleUserInput(const std::string& input) {
    if (handleSpecialCommands(input)) {
        return true;
    }
    
    MoveResult result = engine.makeMove(input);
    handleMoveResult(result);
    
    return false;
}

bool CommandLineDisplay::handleSpecialCommands(const std::string& input) {
    if (input == "quit" || input == "exit") {
        std::cout << "Thanks for playing!\n";
        engine.endGame("Game ended by player");
        return true;
    }
    
    if (input == "help") {
        displayHelp();
        return true;
    }
    
    return false;
}

void CommandLineDisplay::handleMoveResult(MoveResult result) {
    switch (result) {
        case MoveResult::SUCCESS:
            // Move was successful, no message needed
            break;
            
        case MoveResult::INVALID_FORMAT:
            std::cout << "Invalid move format! Use format like 'A2->A3' or 'A2-A3' or 'A2 A3'\n";
            std::cout << "Please try again.\n";
            break;
            
        case MoveResult::INVALID_MOVE:
            std::cout << "Invalid move! Please check the rules and try again.\n";
            std::cout << "Please try again.\n";
            break;
            
        case MoveResult::GAME_OVER:
            std::cout << "The game is already over!\n";
            break;
    }
}

std::string CommandLineDisplay::colorToString(Color color) {
    return (color == Color::WHITE) ? "White" : "Black";
}

std::string CommandLineDisplay::gameStatusToString(GameStatus status) {
    switch (status) {
        case GameStatus::IN_PROGRESS: return "In Progress";
        case GameStatus::CHECK: return "Check";
        case GameStatus::CHECKMATE: return "Checkmate";
        case GameStatus::STALEMATE: return "Stalemate";
        case GameStatus::ENDED_BY_PLAYER: return "Ended by Player";
        default: return "Unknown";
    }
} 