#include <iostream>
#include "terminal.h"

// This is an example application using the terminal class to create a simple
// tic-tac-toe board. Note that this *isn't* an example of how to do any of this
// *well*. It's a quickly slapped together example, and nothing here is idiomatic
// object-oriented programming. The idea is to show you the things needed to make
// something basic work.

// draw a character of the board
void drawChar(bool showCursor, int cursor[2], char arr[][4], int j, int i) {
    Terminal& t = Terminal::getTerm();
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

// Draw the entire board
void drawBoard(int cursor[2], char arr[3][4]) {
    Terminal& t = Terminal::getTerm();
    // first clear the screen and then draw
    t.clearScreen();
    t.colorBg(Terminal::Black);
    for (int j=0; j<3; j++) {
        for (int i=0; i<3; i++) {
            drawChar(true, cursor, arr, j, i);
        }
        std::cout << std::endl;
    }
}

int main() {
    // Primitive board
    char arr[3][4] = {"X O", "OXO", "X  "};
    // Primitive cursor
    int cursor[2] = {1,1};
    Terminal& t = Terminal::getTerm();
    // To draw with color and get unbuffered input, we need draw mode
    t.drawMode(true);
    drawBoard(cursor, arr);

    while (true) {
        // Read a character from the terminal
        // Note that in Draw Mode, this is the *only* way to read!
        std::pair<Terminal::Code, char> p = t.readChar();
        if ((p.first == Terminal::DownCode || p.second == 'j') &&
                cursor[0] < 3) cursor[0]++;
        else if ((p.first == Terminal::UpCode || p.second == 'k') &&
                cursor[0] > 1) cursor[0]--;
        else if ((p.first == Terminal::LeftCode || p.second == 'h') &&
                cursor[1] > 1) cursor[1]--;
        else if ((p.first == Terminal::RightCode || p.second == 'l') &&
                cursor[1] < 3) cursor[1]++;
        else if (p.second == 'q') break;
        drawBoard(cursor, arr);
    }
    // We're done with draw mode
    t.drawMode(false);
    // Now we can just do regular output/input
    int x;
    std::cin >> x;
    std::cout << "done " << x;
}

