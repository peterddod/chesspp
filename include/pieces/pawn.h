#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c, PieceType::PAWN) {}
    bool isValidMove(const Position& from, const Position& to, const ChessBoard& board) const override;
    char getSymbol() const override { return color == Color::WHITE ? 'P' : 'p'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Pawn>(*this); }
};

#endif 