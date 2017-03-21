#include <iostream>
#include "terminal.h"

void drawChar(bool showCursor, int cursor[2], char arr[][4], int j, int i) {
    Terminal& t = Terminal::getTerm();
    t.showCursor(false);
    char c = arr[j][i];
    if (showCursor && cursor[0] - 1 == j && cursor[1] - 1 == i) {
        t.setNegative(true);
    } else t.setNegative(false);
    if (c == 'X') {
        t.colorFg(true, Terminal::Yellow);
        std::cout << 'X';
    } else if (c == 'O') {
        t.colorFg(true, Terminal::Blue);
        std::cout << 'O';
    } else std::cout << ' ';
    std::cout << std::flush;
}

void drawBoard(int cursor[2], char arr[3][4]) {
    Terminal& t = Terminal::getTerm();
    t.clearScreen();
    t.setCursor(1,1);
    t.colorBg(Terminal::Black);
    for (int j=0; j<3; j++) {
        for (int i=0; i<3; i++) {
            drawChar(true, cursor, arr, j, i);
        }
        std::cout << std::endl;
    }
}

int main() {
    char arr[3][4] = {"X O", "OXO", "X  "};
    int cursor[2] = {1,1};
    drawBoard(cursor, arr);

    Terminal& t = Terminal::getTerm();
    while (true) {
        auto p = t.readChar();
        switch (p.second) {
            case 'j': case 'k': case 'h': case 'l':
                if (p.second == 'j' && cursor[0] < 3) cursor[0]++;
                else if (p.second == 'k' && cursor[0] > 1) cursor[0]--;
                else if (p.second == 'h' && cursor[1] > 1) cursor[1]--;
                else if (p.second == 'l' && cursor[1] < 3) cursor[1]++;
                drawBoard(cursor, arr);
        }
    }
    t.resetRead();
}
