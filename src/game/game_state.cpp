#include "../../include/game_state.h"

void GameState::switchPlayer() {
    currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
}

void GameState::setGameResult(const std::string& result) {
    gameResult = result;
}

void GameState::endGame(const std::string& result) {
    gameOver = true;
    gameResult = result;
} 