#include "../../include/board_renderer.h"
#include <iostream>

void BoardRenderer::displayBoard(const ChessBoard& board, const GameState& state) {
    std::cout << "\n";
    displayRowSeparator();
    
    for (int i = 0; i < ChessBoard::BOARD_SIZE; i++) {
        std::cout << (ChessBoard::BOARD_SIZE - i) << " |";
        for (int j = 0; j < ChessBoard::BOARD_SIZE; j++) {
            const Piece* piece = board.getPiece(Position(i, j));
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
    
    std::cout << "Current player: " << colorToString(state.getCurrentPlayer()) << "\n";
    std::cout << "Legend: Uppercase = White pieces, Lowercase = Black pieces\n";
    std::cout << "P/p = Pawn, R/r = Rook, N/n = Knight, B/b = Bishop, Q/q = Queen, K/k = King\n\n";
}

void BoardRenderer::displayWelcome() {
    std::cout << "========================================\n";
    std::cout << "         Welcome to Chess Game!        \n";
    std::cout << "========================================\n\n";
    std::cout << "This is a two-player chess game.\n";
    std::cout << "White pieces are represented by uppercase letters.\n";
    std::cout << "Black pieces are represented by lowercase letters.\n\n";
    displayHelp();
}

void BoardRenderer::displayHelp() {
    std::cout << "How to play:\n";
    std::cout << "- Enter moves in the format: A2->A3 or A2-A3 or A2 A3\n";
    std::cout << "- Columns are labeled A-H, rows are labeled 1-8\n";
    std::cout << "- White starts first\n";
    std::cout << "- Type 'quit' to exit the game\n";
    std::cout << "- Type 'help' to see this message again\n\n";
}

void BoardRenderer::displayGameResult(const std::string& result) {
    std::cout << "\n========================================\n";
    std::cout << "                GAME OVER               \n";
    std::cout << "========================================\n";
    std::cout << result << "\n";
    std::cout << "========================================\n\n";
}

void BoardRenderer::displayColumnHeaders() {
    std::cout << "    A   B   C   D   E   F   G   H\n\n";
}

void BoardRenderer::displayRowSeparator() {
    std::cout << "  +---+---+---+---+---+---+---+---+\n";
}

std::string BoardRenderer::colorToString(Color color) {
    return (color == Color::WHITE) ? "White" : "Black";
} 