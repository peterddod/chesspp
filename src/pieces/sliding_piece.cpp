#include "../../include/sliding_piece.h"
#include "../../include/path_validator.h"
#include "../../include/chessboard.h"

bool SlidingPiece::isValidSlidingMove(const Position& from, const Position& to, 
                                     const std::vector<Direction>& directions,
                                     const ChessBoard& board) const {
    bool validDirection = false;
    
    for (Direction dir : directions) {
        switch (dir) {
            case Direction::HORIZONTAL:
            case Direction::VERTICAL:
                if (PathValidator::isStraightPath(from, to)) {
                    validDirection = true;
                }
                break;
            case Direction::DIAGONAL:
                if (PathValidator::isDiagonalPath(from, to)) {
                    validDirection = true;
                }
                break;
        }
        if (validDirection) break;
    }
    
    if (!validDirection) return false;
    
    return PathValidator::isPathClear(from, to, board);
} 