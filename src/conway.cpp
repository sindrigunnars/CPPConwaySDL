#include "conway.h"


ConwayGame::ConwayGame(int w, int h) : w(w), h(h) {
    board = new int*[h];
    for (int i = 0; i < h; i++) {
        board[i] = new int[w];
        memset(board[i], 0, w * sizeof(int));
    }
    win = new Window(w, h, "Conway's Game of Life");
}

ConwayGame::~ConwayGame() {
    for (int i = 0; i < h; i++) {
        delete[] board[i];
    }
    delete[] board;
    delete win;
}

void ConwayGame::update_game() {
    alive.push_back(std::pair<int,int>(rand() % w,rand() % h));
}

int ConwayGame::run() {
    int quit = 0;
    int pause = 0;
    while (!quit) {
        if (!pause) update_game();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = SDL_TRUE;
                    break;
                
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_SPACE:
                            pause = !pause;
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
        win->update(alive);
        SDL_Delay(!pause ? delay : 50);
        if (!pause) alive.clear();
    }
    return 0;
}