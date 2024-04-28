#ifndef CONWAY_GAME_LIFE
#define CONWAY_GAME_LIFE
#include <vector>
#include <iostream>
#include "window.h"
#include <SDL2/SDL.h>

class ConwayGame {
public:
    ConwayGame(int w, int h);
    ~ConwayGame();
    int run();
    void update_game();
private:
    int w, h, delay = 500;
    std::vector<std::pair<int,int>> alive;
    int** board;
    Window* win;
};



#endif