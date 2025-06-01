#ifndef TYPES_H
#define TYPES_H

enum class Color { WHITE, BLACK };
enum class PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum class MoveType { NORMAL, CASTLE, EN_PASSANT, PROMOTION };

struct Position {
    int row, col;
    Position(int r = 0, int c = 0) : row(r), col(c) {}
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
    bool isValid() const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }
};

enum class Direction {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL
};

#endif 