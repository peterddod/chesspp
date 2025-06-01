#include "../../include/chess_game.h"
#include "../../include/board_renderer.h"
#include "../../include/move_parser.h"
#include "../../include/move_validator.h"
#include <iostream>
#include <string>

void ChessGame::play() {
    BoardRenderer::displayWelcome();
    
    while (!state.isGameOver()) {
        BoardRenderer::displayBoard(board, state);
        
        std::cout << "Enter your move (or 'quit' to exit, 'help' for help): ";
        std::string input;
        std::getline(std::cin, input);
        
        if (handleSpecialCommands(input)) {
            continue;
        }
        
        if (processMove(input)) {
            state.switchPlayer();
            checkGameEnd();
        } else {
            std::cout << "Please try again.\n";
        }
        
        std::cout << "\n";
    }
    
    BoardRenderer::displayGameResult(state.getGameResult());
}

bool ChessGame::processMove(const std::string& input) {
    Move move = MoveParser::parseMove(input);
    
    if (!move.isValid()) {
        std::cout << "Invalid move format! Use format like 'A2->A3' or 'A2-A3' or 'A2 A3'\n";
        return false;
    }
    
    if (!MoveValidator::validateMove(move, board, state)) {
        return false;
    }
    
    return board.executeMove(move);
}

void ChessGame::checkGameEnd() {
    Color currentPlayer = state.getCurrentPlayer();
    
    if (board.isInCheck(currentPlayer)) {
        if (board.isCheckmate(currentPlayer)) {
            Color winner = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
            std::string result = (winner == Color::WHITE ? "White" : "Black") + std::string(" wins by checkmate!");
            state.endGame(result);
            return;
        } else {
            std::cout << (currentPlayer == Color::WHITE ? "White" : "Black") << " is in check!\n";
        }
    }
}

bool ChessGame::handleSpecialCommands(const std::string& input) {
    if (input == "quit" || input == "exit") {
        std::cout << "Thanks for playing!\n";
        state.endGame("Game ended by player");
        return true;
    }
    
    if (input == "help") {
        BoardRenderer::displayHelp();
        return true;
    }
    
    return false;
} 