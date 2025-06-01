#include "../../include/move.h"

Move::Move(const Position& f, const Position& t, MoveType mt) 
    : from(f), to(t), type(mt) {}

bool Move::isValid() const {
    return from.isValid() && to.isValid() && from != to;
}

std::string Move::toString() const {
    if (!isValid()) return "Invalid";
    
    char fromCol = 'A' + from.col;
    char fromRow = '8' - from.row;
    char toCol = 'A' + to.col;
    char toRow = '8' - to.row;
    
    return std::string(1, fromCol) + std::string(1, fromRow) + 
           "->" + std::string(1, toCol) + std::string(1, toRow);
}

bool Move::operator==(const Move& other) const {
    return from == other.from && to == other.to && type == other.type;
}

bool Move::operator!=(const Move& other) const {
    return !(*this == other);
} 