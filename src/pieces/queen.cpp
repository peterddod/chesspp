#include "../../include/pieces/queen.h"

bool Queen::isValidMove(const Position& from, const Position& to, const ChessBoard& board) const {
    return isValidSlidingMove(from, to, {Direction::HORIZONTAL, Direction::VERTICAL, Direction::DIAGONAL}, board);
} 