#ifndef _GAME_H__
#define _GAME_H__
#include <vector>
#include "Gui.h"
#include "Item.h"
using namespace std;

class Item;
enum towards {DOWN, UP, LEFT, RIGHT};

class Game {
public:
    Gui gui;
    vector<vector<Item*>> privious_items = {};
    vector<vector<Item*>> items = {};
    bool gameover = false;
    size_t privious_score = 0;
    size_t score = 0;
    size_t update_count = 0;
    Game();
    ~Game();
    bool update();
    void paintat(size_t ro, size_t cl, char c) {gui.paintat(ro, cl, c);}
    void prmsg(size_t ro, size_t cl, const char* msg) {gui.prMsg(ro, cl, msg);}
    void update_towards(towards t);
    void goback();
    bool gamedt();
    void win();
    void clean_all();
};
#endif
