#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H

#include "chessboard.h"
#include "game_state.h"

class BoardRenderer {
public:
    static void displayBoard(const ChessBoard& board, const GameState& state);
    static void displayWelcome();
    static void displayHelp();
    static void displayGameResult(const std::string& result);
    
private:
    static void displayColumnHeaders();
    static void displayRowSeparator();
    static std::string colorToString(Color color);
};

#endif 