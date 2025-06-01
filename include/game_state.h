#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "types.h"
#include <string>

class GameState {
private:
    Color currentPlayer;
    bool gameOver;
    std::string gameResult;
    
public:
    GameState() : currentPlayer(Color::WHITE), gameOver(false) {}
    
    void switchPlayer();
    bool isGameOver() const { return gameOver; }
    Color getCurrentPlayer() const { return currentPlayer; }
    void setGameResult(const std::string& result);
    std::string getGameResult() const { return gameResult; }
    void endGame(const std::string& result);
};

#endif 