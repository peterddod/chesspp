#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "types.h"
#include "move.h"
#include "piece.h"
#include <vector>
#include <memory>

// Forward declarations for optimization
struct MoveList;

class ChessBoard {
private:
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    
    // Cached king positions for performance
    mutable Position whiteKingPos;
    mutable Position blackKingPos;
    mutable bool kingPositionsCached;
    
    // Optimization helpers
    void updateKingPositions() const;
    void generatePieceMoves(const Position& from, std::vector<Move>& moves) const;
    bool isSquareAttacked(const Position& pos, Color byColor) const;
    bool makeTemporaryMove(const Move& move, std::unique_ptr<Piece>& capturedPiece);
    void undoTemporaryMove(const Move& move, std::unique_ptr<Piece>& capturedPiece);
    
public:
    ChessBoard();
    ChessBoard(const ChessBoard& other);
    ChessBoard& operator=(const ChessBoard& other);
    void initializeBoard();
    
    // Board access
    const Piece* getPiece(const Position& pos) const;
    Piece* getPiece(const Position& pos);
    void setPiece(const Position& pos, std::unique_ptr<Piece> piece);
    void removePiece(const Position& pos);
    
    // Move execution
    bool executeMove(const Move& move);
    
    // Game state queries
    bool isInCheck(Color playerColor) const;
    bool isCheckmate(Color playerColor) const;
    Position findKing(Color playerColor) const;
    std::vector<Position> getAllPossibleMoves(Color playerColor) const;
    
    // Validation helpers
    bool wouldBeInCheck(const Move& move, Color playerColor) const;
    
    // Board dimensions
    static constexpr int BOARD_SIZE = 8;
    
    // Invalidate caches when board changes
    void invalidateCache();
};

#endif 