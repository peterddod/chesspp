#ifndef ROOK_H
#define ROOK_H

#include "../sliding_piece.h"

class Rook : public SlidingPiece {
public:
    Rook(Color c) : SlidingPiece(c, PieceType::ROOK) {}
    bool isValidMove(const Position& from, const Position& to, const ChessBoard& board) const override;
    char getSymbol() const override { return color == Color::WHITE ? 'R' : 'r'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Rook>(*this); }
};

#endif 