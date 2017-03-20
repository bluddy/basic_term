#include "terminal.h"

Terminal* Terminal::g_terminal = NULL;

Terminal& Terminal::getTerm() {
    if (!Terminal::g_terminal) {
        g_terminal = new Terminal();
    }
    return *g_terminal;
}
