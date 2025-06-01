#ifndef COMMAND_LINE_DISPLAY_H
#define COMMAND_LINE_DISPLAY_H

#include "chesspp.h"
#include <string>

class CommandLineDisplay {
private:
    ChessPP engine;
    
public:
    CommandLineDisplay() = default;
    void play();
    
private:
    void displayWelcome();
    void displayHelp();
    void displayBoard();
    void displayGameResult();
    void displayCurrentPlayer();
    void displayColumnHeaders();
    void displayRowSeparator();
    void displayGameStatus();
    
    bool handleUserInput(const std::string& input);
    bool handleSpecialCommands(const std::string& input);
    void handleMoveResult(MoveResult result);
    
    std::string colorToString(Color color);
    std::string gameStatusToString(GameStatus status);
};

#endif 