#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : public Piece {
public:
    King(Color c) : Piece(c, PieceType::KING) {}
    bool isValidMove(const Position& from, const Position& to, const ChessBoard& board) const override;
    char getSymbol() const override { return color == Color::WHITE ? 'K' : 'k'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<King>(*this); }
};

#endif 