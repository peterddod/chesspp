#ifndef CHESSPP_H
#define CHESSPP_H

#include "chessboard.h"
#include "game_state.h"
#include "move.h"
#include <string>
#include <vector>

enum class MoveResult {
    SUCCESS,
    INVALID_FORMAT,
    INVALID_MOVE,
    GAME_OVER
};

enum class GameStatus {
    IN_PROGRESS,
    CHECK,
    CHECKMATE,
    STALEMATE,
    ENDED_BY_PLAYER
};

class ChessPP {
private:
    ChessBoard board;
    GameState state;
    
public:
    ChessPP();
    
    // Core engine functionality
    MoveResult makeMove(const std::string& moveStr);
    MoveResult makeMove(const Move& move);
    
    // Game state queries
    GameStatus getGameStatus() const;
    Color getCurrentPlayer() const;
    bool isGameOver() const;
    std::string getGameResult() const;
    
    // Board access (read-only)
    const ChessBoard& getBoard() const;
    const Piece* getPieceAt(const Position& pos) const;
    
    // Game control
    void resetGame();
    void endGame(const std::string& result);
    
    // Move validation without executing
    bool isValidMove(const std::string& moveStr) const;
    bool isValidMove(const Move& move) const;
    
    // Get all possible moves for current player
    std::vector<Move> getPossibleMoves() const;
    std::vector<Position> getPossibleMovesFrom(const Position& from) const;
    
private:
    void checkGameEnd();
    GameStatus determineGameStatus() const;
};

#endif 