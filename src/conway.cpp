#include "conway.h"


ConwayGame::ConwayGame(int w, int h) : w(w), h(h) {
    board = new uint8_t*[h];
    for (int i = 0; i < h; i++) {
        board[i] = new uint8_t[w];
        memset(board[i], 0, w * sizeof(uint8_t));
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
    alive.clear();
    alive.push_back(std::pair<int,int>(rand() % w,rand() % h));
}

void ConwayGame::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = !running;
                break;
            
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_SPACE:
                        paused = !paused;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEMOTION:
                win->handleMouse(event.motion.x, event.motion.y);
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_ENTER && !win->get_mouse_state())
                    win->set_mouse_state(true);
                else if (event.window.event == SDL_WINDOWEVENT_LEAVE && win->get_mouse_state())
                    win->set_mouse_state(false);
                break;
        }
    }
}

int ConwayGame::run() {
    uint32_t prevFrameTime = SDL_GetTicks();
    uint32_t currFrameTime;
    uint32_t frameDelay = 1000 / 60; // 60 FPS
    while (running) {
        handle_events();

        currFrameTime = SDL_GetTicks();
        if (!paused && currFrameTime - prevFrameTime >= delay) {
            update_game();
            prevFrameTime = currFrameTime;
        }

        win->update(alive);

        uint32_t elapsedTime = SDL_GetTicks() - currFrameTime;
        if (elapsedTime < frameDelay) {
            SDL_Delay(frameDelay - elapsedTime);
        }
    }
    return 0;
}