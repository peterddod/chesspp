#ifndef MOVE_H
#define MOVE_H

#include "types.h"
#include <string>

class Move {
public:
    Position from;
    Position to;
    MoveType type;
    
    Move(const Position& f, const Position& t, MoveType mt = MoveType::NORMAL);
    bool isValid() const;
    std::string toString() const;
    
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;
};

#endif 