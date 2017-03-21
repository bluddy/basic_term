#ifndef PROMPTS_H
#define PROMPTS_H

#include <iostream>
#include <string>

class Prompts {
    public:
    static void stats(int num, int white, int black) {
        std::cout << "Game " << num << '\n'
            << "White wins: " << white << ", Black wins: " << black << '\n' << std::endl;
    }

    static void interface() {
        std::cout << "Choose 1.Text or 2.Cursor interface\n";
    }

    static const char *getWhite(bool white) {
        if (white) return "White";
        else return "Black";
    }

    static void playerPrompt(bool white, int turn) {
        std::cout << getWhite(white) << " turn " << turn << ':' << std::endl;
    }

    static void check(bool white) {
        std::cout << getWhite(white) << " Checks!" << std::endl;
    }

    static void capture(bool white) {
        std::cout << getWhite(white) << " Captures" << std::endl;
    }

    static void outsideBoard() {
        std::cout << "The location specified is outside the board\n";
    }

    static void blocked() {
        std::cout << "This move is blocked by another piece\n";
    }

    static void cannotCastle() {
        std::cout << "Castling is now forbidden with these pieces\n";
    }

    static void mustHandleCheck() {
        std::cout << "You are currently checked and cannot make this move\n";
    }

    static void illegalMove() {
        std::cout << "This move is illegal\n";
    }

    static void checkMate(bool white) {
        std::cout << getWhite(white) << " checkmates!!!\n";
    }

    static void victory(bool white, int turn) {
        std::cout << getWhite(white) << " wins on turn " << turn << std::endl;
    }
};


#endif
