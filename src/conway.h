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
private:
    int w, h, delay = 500, paused = 0, running = 1;
    std::vector<std::pair<int,int>> alive;
    uint8_t** board;
    Window* win;

    void handle_events();
    void update_game();
};



#endif