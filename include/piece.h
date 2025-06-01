#ifndef PIECE_H
#define PIECE_H

#include "types.h"
#include <memory>

// Forward declaration
class ChessBoard;

class Piece {
public:
    Color color;
    PieceType type;
    bool hasMoved;
    
    Piece(Color c, PieceType t) : color(c), type(t), hasMoved(false) {}
    virtual ~Piece() = default;
    virtual bool isValidMove(const Position& from, const Position& to, const ChessBoard& board) const = 0;
    virtual char getSymbol() const = 0;
    virtual std::unique_ptr<Piece> clone() const = 0;
};

#endif 