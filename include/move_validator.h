#ifndef MOVE_VALIDATOR_H
#define MOVE_VALIDATOR_H

#include "move.h"
#include "chessboard.h"
#include "game_state.h"

class MoveValidator {
public:
    static bool validateMove(const Move& move, const ChessBoard& board, const GameState& state);
    
private:
    static bool hasCorrectOwnership(const Move& move, const ChessBoard& board, Color currentPlayer);
    static bool followsPieceRules(const Move& move, const ChessBoard& board);
    static bool wouldNotCauseCheck(const Move& move, const ChessBoard& board, Color currentPlayer);
    static bool isDestinationValid(const Move& move, const ChessBoard& board, Color currentPlayer);
};

#endif 