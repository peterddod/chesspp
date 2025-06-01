#ifndef QUEEN_H
#define QUEEN_H

#include "../sliding_piece.h"

class Queen : public SlidingPiece {
public:
    Queen(Color c) : SlidingPiece(c, PieceType::QUEEN) {}
    bool isValidMove(const Position& from, const Position& to, const ChessBoard& board) const override;
    char getSymbol() const override { return color == Color::WHITE ? 'Q' : 'q'; }
    std::unique_ptr<Piece> clone() const override { return std::make_unique<Queen>(*this); }
};

#endif 