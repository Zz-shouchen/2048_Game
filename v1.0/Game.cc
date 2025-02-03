#include "Game.h"
#include "Gui.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string.h>

Game::Game(){
    gui.init();
    gui.clear();
    for(int i=0;i<Box_num_row;i++){
        vector<Item*> temp1(Box_num_col);
        vector<Item*> temp2(Box_num_col);
        for(int j=0;j<Box_num_col;j++){
            temp1[j] = new Item(this,i*Box_row+1,j*Box_col+1,0);
            temp2[j] = new Item(this,i*Box_row+1,j*Box_col+1,0);
        }
        items.push_back(temp1);
        privious_items.push_back(temp2);
            /*
            +----------------------------+
            |+-----++-----++-----++-----+|
            ||     ||     ||     ||     ||
            ||     ||     ||     ||     ||
            ||     ||     ||     ||     ||
            |+-----++-----++-----++-----+|
            |+-----++-----++-----++-----+|
            ||     ||     ||     ||     ||
            ||     ||     ||     ||     ||
            ||     ||     ||     ||     ||
            |+-----++-----++-----++-----+|
            |+-----++-----++-----++-----+|
            ||     ||     ||     ||     ||
            ||     ||     ||     ||     ||
            ||     ||     ||     ||     ||
            |+-----++-----++-----++-----+|
            |+-----++-----++-----++-----+|
            ||     ||     ||     ||     ||
            ||     ||     ||     ||     ||
            ||     ||     ||     ||     ||
            |+-----++-----++-----++-----+|
            +----------------------------+
            */
    }
    privious_score = 0;
    score = 0;
    items[Box_num_row/2][Box_num_col/2]->value = 2;
}

Game::~Game(){
    clean_all();
}

bool Game::update(){
    update_count++;
    if(update_count >=100)update_count = 0;
    gui.clear();
    gui.printMsg(3, MAXCOL+2, "score: ", score);
    gui.printMsg(4, MAXCOL+2, "update_count: ", update_count);
    if(!items.empty()){
        for(int i=0;i<Box_num_row;i++){
            for(int j=0;j<Box_num_col;j++){
                items[i][j]->paintss();
            }
        }
    }
    gui.redraw();
    int c = 0;
    while(!(KEY_DOWN<=c && c<=KEY_RIGHT || c == 'q' || c == 'l' || c == ' '))c = getch();
    if(c == 'q'){
        clean_all();
        return false;
        }
    if(c == 'l'){
        goback();
        score = privious_score;
        if (gamedt())return false;
        return true;
        }
    if(c != 'l'){
        for(int i=0;i<Box_num_row;i++){
            for(int j=0;j<Box_num_col;j++){
                delete privious_items[i][j];
                privious_items[i][j] = new Item(*items[i][j]);
            }
        }
        privious_score = score;
        update_towards(towards(c - KEY_DOWN));
        bool add_factor = true;
        while(add_factor){
            bool sumup = true;
            for(int i=0;i<Box_num_row;i++){
                for(int j=0;j<Box_num_col;j++){
                    if(items[i][j]->value != 0)continue;
                    sumup = false;
                    int a = rand() % (Box_num_col*Box_num_row);
                    if(a == 0 && items[i][j]->value == 0 && add_factor){
                        items[i][j]->value = 2;
                        add_factor = false;
                        break;
                    }
                }
            }
            if(sumup)break;
        }
    }
    if (gamedt())return false;
    return true;
}

void Game::update_towards(towards t){
    for(int con=0;con<Box_num_col - 1 || con<Box_num_row - 1;con++){
        int cout = 0;
        for(int i=0;i<Box_num_row;i++){
            for(int j=0;j<Box_num_col;j++){
                if(items[i][j]->value == 0)continue;
                switch(t){
                    case UP:
                        if(i == 0)continue;
                        if(items[i-1][j]->value == 0){
                            items[i-1][j]->value = items[i][j]->value;
                            items[i][j]->value = 0;
                            cout = 1;
                        }
                        break;
                    case DOWN:
                        if(i == Box_num_row - 1)continue;
                        if(items[i+1][j]->value == 0){
                            items[i+1][j]->value = items[i][j]->value;
                            items[i][j]->value = 0;
                            cout = 1;
                        }
                        break;
                    case LEFT:
                        if(j == 0)continue;
                        if(items[i][j-1]->value == 0){
                            items[i][j-1]->value = items[i][j]->value;
                            items[i][j]->value = 0;
                            cout = 1;
                        }
                        break;
                    case RIGHT:
                        if(j == Box_num_col - 1)continue;
                        if(items[i][j+1]->value == 0){
                            items[i][j+1]->value = items[i][j]->value;
                            items[i][j]->value = 0;
                            cout = 1;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if(cout == 0)break;
    }
    switch(t){
        case UP:
            for(int i=1;i<Box_num_row;i++){
                for(int j=0;j<Box_num_col;j++){
                    if(items[i][j]->value == 0)continue;
                    if(items[i-1][j]->value == items[i][j]->value){
                        items[i-1][j]->value *= 2;
                        items[i][j]->value = 0;
                        score += items[i-1][j]->value;
                    }
                }
            }
            break;
        case DOWN:
            for(int i=Box_num_row-2;i>=0;i--){
                for(int j=0;j<Box_num_col;j++){
                    if(items[i][j]->value == 0)continue;
                    if(items[i+1][j]->value == items[i][j]->value){
                        items[i+1][j]->value *= 2;
                        items[i][j]->value = 0;
                        score += items[i+1][j]->value;
                    }
                }
            }
            break;
        case LEFT:
            for(int i=0;i<Box_num_row;i++){
                for(int j=1;j<Box_num_col;j++){
                    if(items[i][j]->value == 0)continue;
                    if(items[i][j-1]->value == items[i][j]->value){
                        items[i][j-1]->value *= 2;
                        items[i][j]->value = 0;
                        score += items[i][j-1]->value;
                    }
                }
            }
            break;
        case RIGHT:
            for(int i=0;i<Box_num_row;i++){
                for(int j=Box_num_col-2;j>=0;j--){
                    if(items[i][j]->value == 0)continue;
                    if(items[i][j+1]->value == items[i][j]->value){
                        items[i][j+1]->value *= 2;
                        items[i][j]->value = 0;
                        score += items[i][j+1]->value;
                    }
                }
            }
            break;
        default:
            break;
        }
    for(int con=0;con<Box_num_col - 2 || con<Box_num_row - 2;con++){
        int cout = 0;
        for(int i=0;i<Box_num_row;i++){
            for(int j=0;j<Box_num_col;j++){
                if(items[i][j]->value == 0)continue;
                switch(t){
                    case UP:
                        if(i == 0)continue;
                        if(items[i-1][j]->value == 0){
                            items[i-1][j]->value = items[i][j]->value;
                            items[i][j]->value = 0;
                            cout = 1;
                        }
                        break;
                    case DOWN:
                        if(i == Box_num_row - 1)continue;
                        if(items[i+1][j]->value == 0){
                            items[i+1][j]->value = items[i][j]->value;
                            items[i][j]->value = 0;
                            cout = 1;
                        }
                        break;
                    case LEFT:
                        if(j == 0)continue;
                        if(items[i][j-1]->value == 0){
                            items[i][j-1]->value = items[i][j]->value;
                            items[i][j]->value = 0;
                            cout = 1;
                        }
                        break;
                    case RIGHT:
                        if(j == Box_num_col - 1)continue;
                        if(items[i][j+1]->value == 0){
                            items[i][j+1]->value = items[i][j]->value;
                            items[i][j]->value = 0;
                            cout = 1;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if(cout == 0)break;
    }
}

void Game::goback(){
    for(int i=0;i<Box_num_row;i++){
        for(int j=0;j<Box_num_col;j++){
            delete items[i][j];
            items[i][j] = new Item(*privious_items[i][j]);
        }
    }
}

bool Game::gamedt(){
    if (gameover){
        gui.clear();
        prmsg(MAXROW / 2, MAXCOL / 2 - 8, "Game Over");
        gui.printMsg(MAXROW / 2 + 1, MAXCOL / 2 - 12, "Your score is: ", score);
        prmsg(MAXROW / 2 + 2, MAXCOL / 2 - 9, "Press q to quit");
        float time_ed = 0;
        while (time_ed < 3){
            time_ed += 0.5;
            int c = gui.get();
            if (c == 'q'){
                clean_all();
                exit(0);
            }
            usleep(500000);
        }
        score = 0;
        return true;
    }
    return false;
}

void Game::win(){
    gui.clear();
    prmsg(MAXROW / 2, MAXCOL / 2 - 8, "You Win");
    gui.printMsg(MAXROW / 2 + 1, MAXCOL / 2 - 12, "Your score is: ", score);
    prmsg(MAXROW / 2 + 2, MAXCOL / 2 - 30, "Press q to quit or wait for new game(The score will be saved)");
    gui.redraw();
    float time_ed = 0;
    while (time_ed < 3){
        time_ed += 0.5;
        int c = gui.get();
        if (c == 'q'){
            clean_all();
            exit(0);
        }
        usleep(500000);
    }
}

void Game::clean_all(){
    gui.end();
    for(int i=0;i<Box_num_row;i++){
        for(int j=0;j<Box_num_col;j++){
            delete items[i][j];
            delete privious_items[i][j];
        }
    }
    items.clear();
    privious_items.clear();
}
