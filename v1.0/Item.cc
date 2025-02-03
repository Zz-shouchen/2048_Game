#include "Item.h"
#include "Game.h"
#include <string>


void Item::paintss(){
    if(value==0)return;
    string chrs = std::to_string(value);
    int w = chrs.length();
    char* s = new char[w+1];
    for(int i=0;i<w;i++){
        s[i]=chrs[i];
    }
    s[w]='\0';
    for(int i=0;i<w && i<Box_col-2;i++){
        game->paintat(row+1,col+i+1,s[i]);
    }
    if(w>Box_col-2){
        for(int i=Box_col-2;i<w && i<Box_col*2-4;i++)game->paintat(row+2,col+i-Box_col+3,s[i]);
        if(w>Box_col*2-4){
            for(int i=Box_col*2-4;i<w;i++)game->paintat(row+3,col+i-Box_col*2+5,s[i]);
        }
    }
    delete[] s;
    init_pair(1,COLOR_RED,COLOR_BLACK);
    attron(COLOR_PAIR(1));
    game->paintat(row,col,'+');
    game->paintat(row+Box_row-1,col,'+');
    game->paintat(row,col+Box_col-1,'+');
    game->paintat(row+Box_row-1,col+Box_col-1,'+');
    attroff(COLOR_PAIR(1));
    init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
    attron(COLOR_PAIR(2));
    for(int i=1;i<Box_row-1;i++){
        game->paintat(row+i,col,'|');
        game->paintat(row+i,col+Box_col-1,'|');
    }
    for(int i=1;i<Box_col-1;i++){
        game->paintat(row,col+i,'-');
        game->paintat(row+Box_row-1,col+i,'-');
    }
    attroff(COLOR_PAIR(2));
}

