#ifndef PATH_VALIDATOR_H
#define PATH_VALIDATOR_H

#include "types.h"
#include <vector>

// Forward declaration
class ChessBoard;

class PathValidator {
public:
    static bool isPathClear(const Position& from, const Position& to, const ChessBoard& board);
    static bool isDiagonalPath(const Position& from, const Position& to);
    static bool isStraightPath(const Position& from, const Position& to);
    static bool isKnightMove(const Position& from, const Position& to);
    
private:
    static std::vector<Position> getPathPositions(const Position& from, const Position& to);
    static std::pair<int, int> getDirection(const Position& from, const Position& to);
};

#endif 