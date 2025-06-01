#include "../../include/path_validator.h"
#include "../../include/chessboard.h"
#include <cmath>

bool PathValidator::isPathClear(const Position& from, const Position& to, const ChessBoard& board) {
    auto positions = getPathPositions(from, to);
    
    for (const auto& pos : positions) {
        if (board.getPiece(pos) != nullptr) {
            return false;
        }
    }
    
    return true;
}

bool PathValidator::isDiagonalPath(const Position& from, const Position& to) {
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);
    return rowDiff == colDiff && rowDiff > 0;
}

bool PathValidator::isStraightPath(const Position& from, const Position& to) {
    return (from.row == to.row && from.col != to.col) || 
           (from.col == to.col && from.row != to.row);
}

bool PathValidator::isKnightMove(const Position& from, const Position& to) {
    int rowDiff = std::abs(to.row - from.row);
    int colDiff = std::abs(to.col - from.col);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

std::vector<Position> PathValidator::getPathPositions(const Position& from, const Position& to) {
    std::vector<Position> positions;
    
    auto [rowDir, colDir] = getDirection(from, to);
    
    int currentRow = from.row + rowDir;
    int currentCol = from.col + colDir;
    
    while (currentRow != to.row || currentCol != to.col) {
        positions.emplace_back(currentRow, currentCol);
        currentRow += rowDir;
        currentCol += colDir;
    }
    
    return positions;
}

std::pair<int, int> PathValidator::getDirection(const Position& from, const Position& to) {
    int rowDir = (to.row > from.row) ? 1 : (to.row < from.row) ? -1 : 0;
    int colDir = (to.col > from.col) ? 1 : (to.col < from.col) ? -1 : 0;
    return {rowDir, colDir};
} 