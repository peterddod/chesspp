#include "../../include/pieces/king.h"
#include <cmath>

bool King::isValidMove(const Position& from, const Position& to, const ChessBoard& board) const {
    (void)board; // King doesn't need to check the board for path clearance (only moves one square)
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);
    
    return rowDiff <= 1 && colDiff <= 1;
} 