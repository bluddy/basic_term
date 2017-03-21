#ifndef TERMINAL
#define TERMINAL

#include <iostream>

static const std::string CSI = "\x1b[";

// The Terminal class abstracts away things we want to do with the terminal
// It is a singleton, and 
class Terminal {
public:
    class Cursor {
    public:
        enum Dir {
            UpDir,
            DownDir,
            LeftDir,
            RightDir
        };
        void move(Dir dir, int n);
        void set(int row, int col);
    };
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
    void setDefault();

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
    void resetRead();

    ~Terminal() {
        setDefault();
        clearScreen();
    }

    Terminal& getTerm();
    Terminal(const Terminal&) = delete;

private:
    Terminal() {}
    static Terminal* g_terminal;
};

#endif
