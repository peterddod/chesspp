#include "../../include/pieces/bishop.h"

bool Bishop::isValidMove(const Position& from, const Position& to, const ChessBoard& board) const {
    return isValidSlidingMove(from, to, {Direction::DIAGONAL}, board);
} 