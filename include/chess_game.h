#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "chessboard.h"
#include "game_state.h"
#include <string>

class ChessGame {
private:
    ChessBoard board;
    GameState state;
    
public:
    ChessGame() = default;
    void play();
    
private:
    bool processMove(const std::string& input);
    void checkGameEnd();
    bool handleSpecialCommands(const std::string& input);
};

#endif 