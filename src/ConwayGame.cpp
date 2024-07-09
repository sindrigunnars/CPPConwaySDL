#include "ConwayGame.h"


ConwayGame::ConwayGame(int w, int h) : w(w), h(h) {
    board = new uint8_t*[h];
    for (int i = 0; i < h; i++) {
        board[i] = new uint8_t[w];
        memset(board[i], 0, w * sizeof(uint8_t));
    }
    win = new GridWindow(w, h, "Conway's Game of Life");
}

ConwayGame::~ConwayGame() {
    for (uint32_t i = 0; i < h; i++) {
        delete[] board[i];
    }
    delete[] board;
    delete win;
}

void ConwayGame::update_game() {
    alive.clear();
    uint8_t** new_board = new uint8_t*[h];
    for (uint32_t i = 0; i < h; ++i) {
        new_board[i] = new uint8_t[w];
        memset(new_board[i], 0, w * sizeof(uint8_t));
    }

    for (uint32_t i = 0; i < h; i++) {
        for (uint32_t j = 0; j < w; j++) {
            int neighbours = num_neighbours(std::make_pair(i, j));
            if (board[i][j] == 1 && (neighbours == 2 || neighbours == 3)) {
                alive.push_back(std::make_pair(j, i));
                new_board[i][j] = 1;
            }
            if (board[i][j] == 0 && neighbours == 3) {
                alive.push_back(std::make_pair(j, i));
                new_board[i][j] = 1;
            }
        }
    }

    for (uint32_t i = 0; i < h; ++i) {
        delete[] board[i];
    }
    delete[] board;
    board = new_board;
}

int ConwayGame::num_neighbours(const std::pair<uint32_t,uint32_t>& coord) {
    int counter = 0;
    if (coord.first > 0      && coord.second > 0     && board[coord.first - 1][coord.second - 1] == 1) counter++;
    if (coord.first > 0      && coord.second < w - 1 && board[coord.first - 1][coord.second + 1] == 1) counter++;
    if (coord.first < h - 1  && coord.second > 0     && board[coord.first + 1][coord.second - 1] == 1) counter++;
    if (coord.first < h - 1  && coord.second < w - 1 && board[coord.first + 1][coord.second + 1] == 1) counter++;
    if (coord.first > 0      && board[coord.first - 1][coord.second] == 1) counter++;
    if (coord.first < h - 1  && board[coord.first + 1][coord.second] == 1) counter++;
    if (coord.second > 0     && board[coord.first][coord.second - 1] == 1) counter++;
    if (coord.second < w - 1 && board[coord.first][coord.second + 1] == 1) counter++;
    return counter;
}

void ConwayGame::handle_events() {
    SDL_Event event;
    std::pair<int,int> coords;
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
                coords = win->setAlive(event.motion.x, event.motion.y);
                if (board[coords.second][coords.first] == 1) {
                    board[coords.second][coords.first] = 0;
                    alive.erase(std::remove(alive.begin(), alive.end(), coords), alive.end());
                } else {
                    board[coords.second][coords.first] = 1;
                    alive.push_back(coords);
                }
                break;
            case SDL_MOUSEMOTION:
                win->handleMouse(event.motion.x, event.motion.y);
                break;
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
