#ifndef _ITEM_H_
#define _ITEM_H_
#include "Game.h"

class Game;

class Item {
public:
    Game* game;
    int row = 0;
    int col = 0;
    size_t value = 0;
    Item(): game(nullptr), row(0), col(0), value(0) {};
    Item(Game* g, int r, int c, size_t v): game(g), row(r), col(c), value(v) {};
    Item(const Item& other): game(other.game), row(other.row), col(other.col), value(other.value) {};
    void paintss();
};
#endif
