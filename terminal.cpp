#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include "terminal.h"

Terminal* Terminal::g_terminal = NULL;

// Save the termios status
static struct termios savedTermios;
static bool rawInput = false;

void setupRawInput() {
    if (!rawInput) {
        tcgetattr(0, &savedTermios);
        struct termios termios = savedTermios;
        termios.c_lflag &= ~ICANON;
        termios.c_lflag &= ~ECHO;
        termios.c_cc[VMIN] = 1;
        termios.c_cc[VTIME] = 0;
        tcsetattr(0, TCSANOW, &termios);
    }
    rawInput = true;
}

void undoRawInput() {
    if (rawInput) {
        tcsetattr(0, TCSANOW, &savedTermios);
    }
    rawInput = false;
}

Terminal& Terminal::getTerm() {
    if (!Terminal::g_terminal) {
        g_terminal = new Terminal();
    }
    return *g_terminal;
}

void Terminal::moveCursor(Dir dir, int n) {
    char c = (dir == UpDir) ? 'A' : (dir == DownDir) ? 'B' :
                 (dir == RightDir) ? 'C' : (dir == LeftDir) ? 'D' : 0;
    if (c) std::cout << CSI << n << c;
}

void Terminal::setCursor(int row, int col) {
    std::cout << CSI << row << ';' << col << 'H';
}

static void show_cursor(bool b) {
    std::cout << CSI << "?25" << (b ? 'h' : 'l');
}

void Terminal::showCursor(bool b) {
    show_cursor(b);
}

void Terminal::colorFg(bool bright, Color color) {
    std::cout << CSI << 30 + color << (bright ? ";1" : "") << "m";
}

void Terminal::colorBg(Color color) {
    std::cout << CSI << 40 + color << "m";
}

void Terminal::colorAll(bool bright, Color foreColor, Color backColor) {
    std::cout << CSI << 30 + foreColor << (bright ? ";1;" : ";") << 40 + backColor << "m";
}

void Terminal::setNegative(bool set) {
    std::cout << CSI << (set ? "7m" : "27m");
}

void set_default() {
    std::cout << CSI << "0m";
}

void Terminal::setDefault() {
    set_default();
}

void Terminal::clearScreen() {
    std::cout << CSI << "2J";
}

std::pair<Terminal::Code, char> Terminal::readChar() {
    if (!rawInput) setupRawInput();
    int result;
    read(0, &result, 1);
    Code cd = result == -1 ? ErrorCode : CharCode;
    char c = result == -1 ? 0 : (char)result;
    return {cd, c};
}

void Terminal::resetRead() {
    undoRawInput();
}

void restore_defaults() {
    show_cursor(true);
    set_default();
}

void signal_handler(int) {
    restore_defaults();
    exit(0);
}

Terminal::Terminal() {
    atexit(restore_defaults);
    signal(SIGINT, signal_handler);
}

Terminal::~Terminal() {
    undoRawInput();
}

