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
            Up,
            Down,
            Left,
            Right
        };
        void move(Dir dir, int n) {
            char c = (dir == Up) ? 'A' : (dir == Down) ? 'B' :
                         (dir == Right) ? 'C' : (dir == Left) ? 'D' : 0;
            if (c) std::cout << CSI << n << c;
        }
        void set(int row, int col) {
            std::cout << CSI << row << ';' << col << 'H';
        }
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
    void setColorFore(bool bright, Color color) {
        std::cout << CSI << 30 + color << (bright ? ";1" : "") << "m";
    }
    void setColorBack(Color color) {
        std::cout << CSI << 40 + color << "m";
    }
    void setColorAll(bool bright, Color foreColor, Color backColor) {
        std::cout << CSI << 30 + foreColor << (bright ? ";1;" : ";") << 40 + backColor << "m";
    }
    void setNegative(bool set) {
        std::cout << CSI << (set ? "7m" : "27m");
    }
    void setDefault() {
        std::cout << CSI << "0m";
    }
    void clearScreen() {
        std::cout << CSI << "2J";
    }
    ~Terminal() {
        setDefault();
        clearScreen();
    }

    Terminal& getTerm();
    Terminal(const Terminal&) = delete;

private:
    static Terminal* g_terminal;
    Terminal() {}
};

#endif
