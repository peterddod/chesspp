#ifndef BISHOP_H
#define BISHOP_H

#include "../sliding_piece.h"

class Bishop : public SlidingPiece {
public:
    Bishop(Color c) : SlidingPiece(c, PieceType::BISHOP) {}
    bool isValidMove(const Position& from, const Position& to, const ChessBoard& board) const override;
    char getSymbol() const override { return color == Color::WHITE ? 'B' : 'b'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Bishop>(*this); }
};

#endif 