#include "../../include/chesspp.h"
#include "../../include/move_parser.h"
#include "../../include/move_validator.h"
#include <algorithm>

ChessPP::ChessPP() {
    board.initializeBoard();
}

MoveResult ChessPP::makeMove(const std::string& moveStr) {
    if (state.isGameOver()) {
        return MoveResult::GAME_OVER;
    }
    
    Move move = MoveParser::parseMove(moveStr);
    
    if (!move.isValid()) {
        return MoveResult::INVALID_FORMAT;
    }
    
    return makeMove(move);
}

MoveResult ChessPP::makeMove(const Move& move) {
    if (state.isGameOver()) {
        return MoveResult::GAME_OVER;
    }
    
    if (!MoveValidator::validateMove(move, board, state)) {
        return MoveResult::INVALID_MOVE;
    }
    
    if (board.executeMove(move)) {
        state.switchPlayer();
        checkGameEnd();
        return MoveResult::SUCCESS;
    }
    
    return MoveResult::INVALID_MOVE;
}

GameStatus ChessPP::getGameStatus() const {
    if (state.isGameOver()) {
        // Parse the game result to determine the specific end condition
        if (state.getGameResult().find("checkmate") != std::string::npos) {
            return GameStatus::CHECKMATE;
        } else if (state.getGameResult().find("stalemate") != std::string::npos) {
            return GameStatus::STALEMATE;
        } else {
            return GameStatus::ENDED_BY_PLAYER;
        }
    }
    
    return determineGameStatus();
}

GameStatus ChessPP::determineGameStatus() const {
    Color currentPlayer = state.getCurrentPlayer();
    
    if (board.isInCheck(currentPlayer)) {
        if (board.isCheckmate(currentPlayer)) {
            return GameStatus::CHECKMATE;
        } else {
            return GameStatus::CHECK;
        }
    }
    
    // TODO: Add stalemate detection
    return GameStatus::IN_PROGRESS;
}

Color ChessPP::getCurrentPlayer() const {
    return state.getCurrentPlayer();
}

bool ChessPP::isGameOver() const {
    return state.isGameOver();
}

std::string ChessPP::getGameResult() const {
    return state.getGameResult();
}

const ChessBoard& ChessPP::getBoard() const {
    return board;
}

const Piece* ChessPP::getPieceAt(const Position& pos) const {
    return board.getPiece(pos);
}

void ChessPP::resetGame() {
    board.initializeBoard();
    state = GameState(); // Reset to initial state
}

void ChessPP::endGame(const std::string& result) {
    state.endGame(result);
}

bool ChessPP::isValidMove(const std::string& moveStr) const {
    Move move = MoveParser::parseMove(moveStr);
    return isValidMove(move);
}

bool ChessPP::isValidMove(const Move& move) const {
    if (!move.isValid()) {
        return false;
    }
    
    return MoveValidator::validateMove(move, board, state);
}

std::vector<Move> ChessPP::getPossibleMoves() const {
    std::vector<Move> moves;
    Color currentPlayer = state.getCurrentPlayer();
    
    for (int row = 0; row < ChessBoard::BOARD_SIZE; ++row) {
        for (int col = 0; col < ChessBoard::BOARD_SIZE; ++col) {
            Position from(row, col);
            const Piece* piece = board.getPiece(from);
            
            if (piece && piece->color == currentPlayer) {
                std::vector<Position> destinations = getPossibleMovesFrom(from);
                for (const Position& to : destinations) {
                    moves.emplace_back(from, to);
                }
            }
        }
    }
    
    return moves;
}

std::vector<Position> ChessPP::getPossibleMovesFrom(const Position& from) const {
    std::vector<Position> moves;
    const Piece* piece = board.getPiece(from);
    
    if (!piece || piece->color != state.getCurrentPlayer()) {
        return moves;
    }
    
    for (int row = 0; row < ChessBoard::BOARD_SIZE; ++row) {
        for (int col = 0; col < ChessBoard::BOARD_SIZE; ++col) {
            Position to(row, col);
            Move move(from, to);
            
            if (isValidMove(move)) {
                moves.push_back(to);
            }
        }
    }
    
    return moves;
}

void ChessPP::checkGameEnd() {
    Color currentPlayer = state.getCurrentPlayer();
    
    if (board.isInCheck(currentPlayer)) {
        if (board.isCheckmate(currentPlayer)) {
            Color winner = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
            std::string result = (winner == Color::WHITE ? "White" : "Black") + std::string(" wins by checkmate!");
            state.endGame(result);
        }
    }
    // TODO: Add stalemate detection logic
} 