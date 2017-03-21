#ifndef TERMINAL
#define TERMINAL

#include <iostream>

// The Terminal class abstracts away things we want to do with the terminal
// It is a singleton, and 
class Terminal {
public:
    enum Dir {
        UpDir,
        DownDir,
        LeftDir,
        RightDir
    };
    void drawMode(bool on);

    enum Color {
        Black = 0,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        Default = 9
    };
    void colorFg(bool bright, Color color);
    void colorBg(Color color);
    void colorAll(bool bright, Color foreColor, Color backColor);
    void setNegative(bool set);

    void clearScreen();

    enum Code {
        CharCode,
        UpCode,
        DownCode,
        LeftCode,
        RightCode,
        ErrorCode
    };
    std::pair<Code, char> readChar();

    static Terminal& getTerm();

    ~Terminal();
    Terminal(const Terminal&) = delete;

private:
    Terminal();
    static Terminal* g_terminal;

    void moveCursor(Dir dir, int n);
    void setCursor(int row, int col);
    void showCursor(bool b);
    void setDefault();
};

#endif
