#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>

// The Terminal class abstracts away things we need to draw to the terminal.
// It's a singleton, so the only way to access it is to call the getTerm()
// function: you can't construct this class.
class Terminal {
public:
    // Call this function to enter 'drawing mode'. In drawing mode, you paint the
    // screen with characters of different background and foreground colors, and
    // all input is immediately captured by the program, character by character.
    // If you want to get back to normal reading/writing mode, turn this mode off.
    void drawMode(bool on);

    // The possible colors. Note that foreground colors can also be 'bright',
    // adding another 8 colors
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
    // Set the foreground color for the next piece of text, keeping the
    // background color as is.
    void colorFg(bool bright, Color color);
    // Set the background color for the next piece of text, keeping the
    // foreground color as is.
    void colorBg(Color color);
    // Set both background and foreground colors at the same time.
    void colorAll(bool bright, Color foreColor, Color backColor);
    // Set negative mode for the next piece of text. This will reverse
    // background and foreground colors, and is great for a cursor.
    void setNegative(bool set);

    // Clear the screen and empty it. Do this before you draw your text image.
    void clearScreen();

    // The possible characters we can return in Draw Mode. CharCode means that
    // it's a regular character stored in the second member of the pair.
    // Up/Down/Left/Right refer to the arrow keys.
    // ErrorCode means something went wrong when reading input.
    enum Code {
        CharCode,
        UpCode,
        DownCode,
        LeftCode,
        RightCode,
        ErrorCode
    };
    // Read a character of input in Draw Mode. This is the *only* way to get
    // input in Draw Mode. No other method will work properly.
    std::pair<Code, char> readChar();

    // Use this static function to get access to the Terminal singleton.
    static Terminal& getTerm();

    ~Terminal();

private:
    enum Dir {
        UpDir,
        DownDir,
        LeftDir,
        RightDir
    };
    Terminal();
    Terminal(const Terminal&) = delete;
    static Terminal* g_terminal;

    void moveCursor(Dir dir, int n);
    void setCursor(int row, int col);
    void showCursor(bool b);
    void setDefault();
};

#endif
