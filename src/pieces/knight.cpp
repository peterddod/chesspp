#include "../../include/pieces/knight.h"
#include "../../include/path_validator.h"

bool Knight::isValidMove(const Position& from, const Position& to, const ChessBoard& board) const {
    (void)board; // Knight doesn't need to check the board for path clearance
    return PathValidator::isKnightMove(from, to);
} 