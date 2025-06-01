#ifndef SLIDING_PIECE_H
#define SLIDING_PIECE_H

#include "piece.h"
#include "types.h"
#include <vector>

class SlidingPiece : public Piece {
public:
    SlidingPiece(Color c, PieceType t) : Piece(c, t) {}
    
protected:
    bool isValidSlidingMove(const Position& from, const Position& to, 
                           const std::vector<Direction>& directions,
                           const ChessBoard& board) const;
};

#endif 