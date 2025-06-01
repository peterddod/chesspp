#ifndef MOVE_PARSER_H
#define MOVE_PARSER_H

#include "move.h"
#include <string>
#include <utility>

class MoveParser {
public:
    static Move parseMove(const std::string& moveStr);
    static Position parsePosition(const std::string& pos);
    static std::string positionToString(const Position& pos);
    
private:
    static std::pair<std::string, std::string> splitMoveString(const std::string& move);
    static std::string cleanString(const std::string& str);
};

#endif 