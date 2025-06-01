#include "../../include/chessboard.h"
#include "../../include/pieces/pawn.h"
#include "../../include/pieces/rook.h"
#include "../../include/pieces/knight.h"
#include "../../include/pieces/bishop.h"
#include "../../include/pieces/queen.h"
#include "../../include/pieces/king.h"
#include <algorithm>

ChessBoard::ChessBoard() : kingPositionsCached(false) {
    board.resize(BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i].resize(BOARD_SIZE);
    }
    initializeBoard();
}

ChessBoard::ChessBoard(const ChessBoard& other) : kingPositionsCached(false) {
    board.resize(BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i].resize(BOARD_SIZE);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (other.board[i][j]) {
                board[i][j] = other.board[i][j]->clone();
            } else {
                board[i][j] = nullptr;
            }
        }
    }
}

ChessBoard& ChessBoard::operator=(const ChessBoard& other) {
    if (this != &other) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (other.board[i][j]) {
                    board[i][j] = other.board[i][j]->clone();
                } else {
                    board[i][j] = nullptr;
                }
            }
        }
    }
    return *this;
}

void ChessBoard::initializeBoard() {
    // Clear the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = nullptr;
        }
    }
    
    // Place black pieces
    board[0][0] = std::make_unique<Rook>(Color::BLACK);
    board[0][1] = std::make_unique<Knight>(Color::BLACK);
    board[0][2] = std::make_unique<Bishop>(Color::BLACK);
    board[0][3] = std::make_unique<Queen>(Color::BLACK);
    board[0][4] = std::make_unique<King>(Color::BLACK);
    board[0][5] = std::make_unique<Bishop>(Color::BLACK);
    board[0][6] = std::make_unique<Knight>(Color::BLACK);
    board[0][7] = std::make_unique<Rook>(Color::BLACK);
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = std::make_unique<Pawn>(Color::BLACK);
    }
    
    // Place white pieces
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[6][i] = std::make_unique<Pawn>(Color::WHITE);
    }
    
    board[7][0] = std::make_unique<Rook>(Color::WHITE);
    board[7][1] = std::make_unique<Knight>(Color::WHITE);
    board[7][2] = std::make_unique<Bishop>(Color::WHITE);
    board[7][3] = std::make_unique<Queen>(Color::WHITE);
    board[7][4] = std::make_unique<King>(Color::WHITE);
    board[7][5] = std::make_unique<Bishop>(Color::WHITE);
    board[7][6] = std::make_unique<Knight>(Color::WHITE);
    board[7][7] = std::make_unique<Rook>(Color::WHITE);
}

const Piece* ChessBoard::getPiece(const Position& pos) const {
    if (!pos.isValid()) return nullptr;
    return board[pos.row][pos.col].get();
}

Piece* ChessBoard::getPiece(const Position& pos) {
    if (!pos.isValid()) return nullptr;
    return board[pos.row][pos.col].get();
}

void ChessBoard::setPiece(const Position& pos, std::unique_ptr<Piece> piece) {
    if (pos.isValid()) {
        board[pos.row][pos.col] = std::move(piece);
    }
}

void ChessBoard::removePiece(const Position& pos) {
    if (pos.isValid()) {
        board[pos.row][pos.col] = nullptr;
    }
}

bool ChessBoard::executeMove(const Move& move) {
    if (!move.isValid()) return false;
    
    Piece* piece = getPiece(move.from);
    if (!piece) return false;
    
    // Execute the move
    std::unique_ptr<Piece> movingPiece = std::move(board[move.from.row][move.from.col]);
    board[move.to.row][move.to.col] = std::move(movingPiece);
    board[move.to.row][move.to.col]->hasMoved = true;
    
    // Invalidate cache since board state changed
    invalidateCache();
    
    return true;
}

Position ChessBoard::findKing(Color playerColor) const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] && 
                board[i][j]->type == PieceType::KING && 
                board[i][j]->color == playerColor) {
                return Position(i, j);
            }
        }
    }
    return Position(-1, -1);
}

void ChessBoard::updateKingPositions() const {
    if (kingPositionsCached) return;
    
    whiteKingPos = Position(-1, -1);
    blackKingPos = Position(-1, -1);
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] && board[i][j]->type == PieceType::KING) {
                if (board[i][j]->color == Color::WHITE) {
                    whiteKingPos = Position(i, j);
                } else {
                    blackKingPos = Position(i, j);
                }
            }
        }
    }
    kingPositionsCached = true;
}

void ChessBoard::invalidateCache() {
    kingPositionsCached = false;
}

bool ChessBoard::isSquareAttacked(const Position& pos, Color byColor) const {
    // Check for pawn attacks first (most common)
    int pawnDirection = (byColor == Color::WHITE) ? -1 : 1;
    int pawnRow = pos.row - pawnDirection;
    
    if (pawnRow >= 0 && pawnRow < BOARD_SIZE) {
        // Check diagonal pawn attacks
        if (pos.col > 0) {
            const Piece* piece = board[pawnRow][pos.col - 1].get();
            if (piece && piece->type == PieceType::PAWN && piece->color == byColor) {
                return true;
            }
        }
        if (pos.col < BOARD_SIZE - 1) {
            const Piece* piece = board[pawnRow][pos.col + 1].get();
            if (piece && piece->type == PieceType::PAWN && piece->color == byColor) {
                return true;
            }
        }
    }
    
    // Check for knight attacks
    static const int knightMoves[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };
    
    for (int i = 0; i < 8; i++) {
        int newRow = pos.row + knightMoves[i][0];
        int newCol = pos.col + knightMoves[i][1];
        
        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
            const Piece* piece = board[newRow][newCol].get();
            if (piece && piece->type == PieceType::KNIGHT && piece->color == byColor) {
                return true;
            }
        }
    }
    
    // Check for king attacks (adjacent squares)
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            
            int newRow = pos.row + dr;
            int newCol = pos.col + dc;
            
            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
                const Piece* piece = board[newRow][newCol].get();
                if (piece && piece->type == PieceType::KING && piece->color == byColor) {
                    return true;
                }
            }
        }
    }
    
    // Check for sliding piece attacks (rook, bishop, queen)
    static const int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // Rook directions
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}  // Bishop directions
    };
    
    for (int dir = 0; dir < 8; dir++) {
        int dr = directions[dir][0];
        int dc = directions[dir][1];
        
        for (int dist = 1; dist < BOARD_SIZE; dist++) {
            int newRow = pos.row + dr * dist;
            int newCol = pos.col + dc * dist;
            
            if (newRow < 0 || newRow >= BOARD_SIZE || newCol < 0 || newCol >= BOARD_SIZE) {
                break;
            }
            
            const Piece* piece = board[newRow][newCol].get();
            if (piece) {
                if (piece->color == byColor) {
                    // Check if this piece can attack in this direction
                    bool canAttack = false;
                    if (dir < 4) { // Horizontal/vertical
                        canAttack = (piece->type == PieceType::ROOK || piece->type == PieceType::QUEEN);
                    } else { // Diagonal
                        canAttack = (piece->type == PieceType::BISHOP || piece->type == PieceType::QUEEN);
                    }
                    if (canAttack) return true;
                }
                break; // Piece blocks further movement in this direction
            }
        }
    }
    
    return false;
}

bool ChessBoard::isInCheck(Color playerColor) const {
    updateKingPositions();
    
    Position kingPos = (playerColor == Color::WHITE) ? whiteKingPos : blackKingPos;
    if (!kingPos.isValid()) return false;
    
    Color opponent = (playerColor == Color::WHITE) ? Color::BLACK : Color::WHITE;
    return isSquareAttacked(kingPos, opponent);
}

void ChessBoard::generatePieceMoves(const Position& from, std::vector<Move>& moves) const {
    const Piece* piece = board[from.row][from.col].get();
    if (!piece) return;
    
    switch (piece->type) {
        case PieceType::PAWN: {
            int direction = (piece->color == Color::WHITE) ? -1 : 1;
            
            // Forward moves
            Position oneForward(from.row + direction, from.col);
            if (oneForward.isValid() && !board[oneForward.row][oneForward.col]) {
                moves.emplace_back(from, oneForward);
                
                // Two squares forward from starting position
                if (!piece->hasMoved) {
                    Position twoForward(from.row + 2 * direction, from.col);
                    if (twoForward.isValid() && !board[twoForward.row][twoForward.col]) {
                        moves.emplace_back(from, twoForward);
                    }
                }
            }
            
            // Diagonal captures
            for (int dc = -1; dc <= 1; dc += 2) {
                Position capture(from.row + direction, from.col + dc);
                if (capture.isValid() && board[capture.row][capture.col] &&
                    board[capture.row][capture.col]->color != piece->color) {
                    moves.emplace_back(from, capture);
                }
            }
            break;
        }
        
        case PieceType::KNIGHT: {
            static const int knightMoves[8][2] = {
                {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                {1, -2}, {1, 2}, {2, -1}, {2, 1}
            };
            
            for (int i = 0; i < 8; i++) {
                Position to(from.row + knightMoves[i][0], from.col + knightMoves[i][1]);
                if (to.isValid() && (!board[to.row][to.col] || 
                    board[to.row][to.col]->color != piece->color)) {
                    moves.emplace_back(from, to);
                }
            }
            break;
        }
        
        case PieceType::KING: {
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    
                    Position to(from.row + dr, from.col + dc);
                    if (to.isValid() && (!board[to.row][to.col] || 
                        board[to.row][to.col]->color != piece->color)) {
                        moves.emplace_back(from, to);
                    }
                }
            }
            break;
        }
        
        case PieceType::ROOK:
        case PieceType::BISHOP:
        case PieceType::QUEEN: {
            // Determine which directions this piece can move
            bool canMoveHorizontalVertical = (piece->type == PieceType::ROOK || piece->type == PieceType::QUEEN);
            bool canMoveDiagonal = (piece->type == PieceType::BISHOP || piece->type == PieceType::QUEEN);
            
            static const int directions[8][2] = {
                {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // Horizontal/vertical
                {-1, -1}, {-1, 1}, {1, -1}, {1, 1}  // Diagonal
            };
            
            for (int dir = 0; dir < 8; dir++) {
                // Skip directions this piece can't move
                if (dir < 4 && !canMoveHorizontalVertical) continue;
                if (dir >= 4 && !canMoveDiagonal) continue;
                
                int dr = directions[dir][0];
                int dc = directions[dir][1];
                
                for (int dist = 1; dist < BOARD_SIZE; dist++) {
                    Position to(from.row + dr * dist, from.col + dc * dist);
                    if (!to.isValid()) break;
                    
                    const Piece* targetPiece = board[to.row][to.col].get();
                    if (targetPiece) {
                        if (targetPiece->color != piece->color) {
                            moves.emplace_back(from, to); // Capture
                        }
                        break; // Can't move further in this direction
                    } else {
                        moves.emplace_back(from, to); // Empty square
                    }
                }
            }
            break;
        }
    }
}

bool ChessBoard::makeTemporaryMove(const Move& move, std::unique_ptr<Piece>& capturedPiece) {
    // Store captured piece
    capturedPiece = std::move(board[move.to.row][move.to.col]);
    
    // Move piece
    board[move.to.row][move.to.col] = std::move(board[move.from.row][move.from.col]);
    
    // Invalidate king position cache if king moved
    if (board[move.to.row][move.to.col]->type == PieceType::KING) {
        invalidateCache();
    }
    
    return true;
}

void ChessBoard::undoTemporaryMove(const Move& move, std::unique_ptr<Piece>& capturedPiece) {
    // Move piece back
    board[move.from.row][move.from.col] = std::move(board[move.to.row][move.to.col]);
    
    // Restore captured piece
    board[move.to.row][move.to.col] = std::move(capturedPiece);
    
    // Invalidate cache
    invalidateCache();
}

bool ChessBoard::wouldBeInCheck(const Move& move, Color playerColor) const {
    // Make temporary move
    std::unique_ptr<Piece> capturedPiece;
    const_cast<ChessBoard*>(this)->makeTemporaryMove(move, capturedPiece);
    
    // Check if in check
    bool inCheck = isInCheck(playerColor);
    
    // Undo move
    const_cast<ChessBoard*>(this)->undoTemporaryMove(move, capturedPiece);
    
    return inCheck;
}

std::vector<Position> ChessBoard::getAllPossibleMoves(Color playerColor) const {
    std::vector<Position> legalMoves;
    legalMoves.reserve(64); // Reserve space for efficiency
    
    // Generate all pseudo-legal moves
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] && board[row][col]->color == playerColor) {
                Position from(row, col);
                std::vector<Move> pieceMoves;
                generatePieceMoves(from, pieceMoves);
                
                // Filter out moves that would leave king in check
                for (const Move& move : pieceMoves) {
                    if (!wouldBeInCheck(move, playerColor)) {
                        legalMoves.push_back(move.to);
                    }
                }
            }
        }
    }
    
    return legalMoves;
}

bool ChessBoard::isCheckmate(Color playerColor) const {
    // First check if player is in check
    if (!isInCheck(playerColor)) {
        return false; // Not in check, so not checkmate
    }
    
    // Generate all legal moves - if any exist, it's not checkmate
    std::vector<Position> legalMoves = getAllPossibleMoves(playerColor);
    return legalMoves.empty();
} 