#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"

class Knight : public Piece {
public:
    Knight(Color c) : Piece(c, PieceType::KNIGHT) {}
    bool isValidMove(const Position& from, const Position& to, const ChessBoard& board) const override;
    char getSymbol() const override { return color == Color::WHITE ? 'N' : 'n'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Knight>(*this); }
};

#endif 