#include "../../include/move_parser.h"
#include <algorithm>
#include <cctype>

Move MoveParser::parseMove(const std::string& moveStr) {
    auto [fromStr, toStr] = splitMoveString(moveStr);
    
    if (fromStr.empty() || toStr.empty()) {
        return Move(Position(-1, -1), Position(-1, -1));
    }
    
    Position from = parsePosition(fromStr);
    Position to = parsePosition(toStr);
    
    return Move(from, to);
}

Position MoveParser::parsePosition(const std::string& pos) {
    if (pos.length() != 2) return Position(-1, -1);
    
    char col = std::toupper(pos[0]);
    char row = pos[1];
    
    if (col < 'A' || col > 'H' || row < '1' || row > '8') {
        return Position(-1, -1);
    }
    
    return Position(8 - (row - '0'), col - 'A');
}

std::string MoveParser::positionToString(const Position& pos) {
    if (!pos.isValid()) return "Invalid";
    
    char col = 'A' + pos.col;
    char row = '8' - pos.row;
    return std::string(1, col) + std::string(1, row);
}

std::pair<std::string, std::string> MoveParser::splitMoveString(const std::string& move) {
    std::string cleanMove = cleanString(move);
    
    size_t arrowPos = cleanMove.find("->");
    if (arrowPos == std::string::npos) {
        arrowPos = cleanMove.find("-");
        if (arrowPos == std::string::npos) {
            arrowPos = cleanMove.find(" ");
        }
    }
    
    if (arrowPos == std::string::npos || arrowPos < 2 || arrowPos + 2 >= cleanMove.length()) {
        return {"", ""};
    }
    
    std::string fromStr = cleanMove.substr(0, arrowPos);
    std::string toStr;
    
    if (cleanMove.substr(arrowPos, 2) == "->") {
        toStr = cleanMove.substr(arrowPos + 2);
    } else {
        toStr = cleanMove.substr(arrowPos + 1);
    }
    
    return {cleanString(fromStr), cleanString(toStr)};
}

std::string MoveParser::cleanString(const std::string& str) {
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
} 