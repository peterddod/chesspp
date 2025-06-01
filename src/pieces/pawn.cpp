#include "../../include/pieces/pawn.h"
#include "../../include/chessboard.h"
#include <cmath>

bool Pawn::isValidMove(const Position& from, const Position& to, const ChessBoard& board) const {
    int direction = (color == Color::WHITE) ? -1 : 1;
    int rowDiff = to.row - from.row;
    int colDiff = std::abs(to.col - from.col);
    
    // Forward move
    if (colDiff == 0) {
        if (rowDiff == direction && !board.getPiece(to)) {
            return true; // One square forward
        }
        if (!hasMoved && rowDiff == 2 * direction && 
            !board.getPiece(to) && !board.getPiece(Position(from.row + direction, from.col))) {
            return true; // Two squares forward from starting position
        }
    }
    // Diagonal capture
    else if (colDiff == 1 && rowDiff == direction && 
             board.getPiece(to) && board.getPiece(to)->color != color) {
        return true;
    }
    
    return false;
} 