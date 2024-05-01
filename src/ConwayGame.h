#ifndef CONWAY_GAME_LIFE
#define CONWAY_GAME_LIFE
#include <vector>
#include <iostream>
#include "GridWindow.h"
#include <SDL2/SDL.h>

class ConwayGame {
public:
    ConwayGame(int w, int h);
    ~ConwayGame();
    int run();
private:
    int w, h, delay = 200, paused = 0, running = 1;
    std::vector<std::pair<int,int>> alive;
    uint8_t** board;
    GridWindow* win;

    void handle_events();
    void update_game();
    int num_neighbours(const std::pair<int,int>& coord);
};



#endif