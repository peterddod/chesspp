#include "../../include/pieces/rook.h"

bool Rook::isValidMove(const Position& from, const Position& to, const ChessBoard& board) const {
    return isValidSlidingMove(from, to, {Direction::HORIZONTAL, Direction::VERTICAL}, board);
} 