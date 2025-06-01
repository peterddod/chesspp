#include "../../include/move_validator.h"
#include <iostream>

bool MoveValidator::validateMove(const Move& move, const ChessBoard& board, const GameState& state) {
    if (!move.isValid()) {
        std::cout << "Invalid move format!\n";
        return false;
    }
    
    if (!hasCorrectOwnership(move, board, state.getCurrentPlayer())) {
        return false;
    }
    
    if (!isDestinationValid(move, board, state.getCurrentPlayer())) {
        return false;
    }
    
    if (!followsPieceRules(move, board)) {
        return false;
    }
    
    if (!wouldNotCauseCheck(move, board, state.getCurrentPlayer())) {
        std::cout << "This move would put your king in check!\n";
        return false;
    }
    
    return true;
}

bool MoveValidator::hasCorrectOwnership(const Move& move, const ChessBoard& board, Color currentPlayer) {
    const Piece* piece = board.getPiece(move.from);
    
    if (!piece) {
        std::cout << "No piece at position " << move.from.col + 'A' << (8 - move.from.row) << "!\n";
        return false;
    }
    
    if (piece->color != currentPlayer) {
        std::cout << "That piece doesn't belong to you!\n";
        return false;
    }
    
    return true;
}

bool MoveValidator::followsPieceRules(const Move& move, const ChessBoard& board) {
    const Piece* piece = board.getPiece(move.from);
    if (!piece) return false;
    
    if (!piece->isValidMove(move.from, move.to, board)) {
        std::cout << "Invalid move for " << 
            (piece->type == PieceType::PAWN ? "pawn" :
             piece->type == PieceType::ROOK ? "rook" :
             piece->type == PieceType::KNIGHT ? "knight" :
             piece->type == PieceType::BISHOP ? "bishop" :
             piece->type == PieceType::QUEEN ? "queen" : "king") << "!\n";
        return false;
    }
    
    return true;
}

bool MoveValidator::wouldNotCauseCheck(const Move& move, const ChessBoard& board, Color currentPlayer) {
    return !board.wouldBeInCheck(move, currentPlayer);
}

bool MoveValidator::isDestinationValid(const Move& move, const ChessBoard& board, Color currentPlayer) {
    const Piece* destinationPiece = board.getPiece(move.to);
    
    if (destinationPiece && destinationPiece->color == currentPlayer) {
        std::cout << "Cannot capture your own piece!\n";
        return false;
    }
    
    return true;
} 