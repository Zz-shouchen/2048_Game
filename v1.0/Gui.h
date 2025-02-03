#ifndef _GUI_H_
#define _GUI_H_
#include <ncurses.h>

int const Box_num_row=4;
int const Box_num_col=4;
int const Box_col=7;
int const Box_row=5;
int const MAXCOL=Box_col*Box_num_col;
int const MAXROW=Box_row*Box_num_row;

class Gui {
    size_t row;
    size_t col;
    WINDOW* win;
public:
    Gui():row(10),col(10) {init();}
    ~Gui() {endwin();}
    void init();
    int get();
    void paintat(size_t, size_t, char);
    void printMsg(int row, int col, const char* prompt, int v);
    void prMsg(int row, int col, const char* prompt);
    void clear();
    void redraw();
    void end() {endwin();}
};
#endif
