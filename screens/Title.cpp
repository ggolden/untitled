#include "Title.h"

void Title::display(Terminal &terminal) {
    terminal.display("Curses!", Position {5, 5});
    terminal.display("a rogue like text adventure", Position {7, 9});
    terminal.display("press any key to start", Position {terminal.rows()-1, terminal.cols() - 22});
}