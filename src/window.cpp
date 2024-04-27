#include "window.h"
#include <iostream>

Window::Window(int cell_w, int cell_h, int cell_s) : cell_width(cell_w), cell_height(cell_h), cell_size(cell_s) {
    window_width = (cell_width * cell_size) + 1;
    window_height = (cell_height * cell_size) + 1;
    
    if (init_win(window_width, window_height) != 0) {
        std::cerr << "Failed to initialize" << std::endl;
    }

    for (int i = 0; i < cell_height; i++) {
        std::vector<SDL_Rect> row;
        for (int j = 0; j < cell_width; j++) {
            SDL_Rect cell = {
                .x = 1 + (j * cell_size),
                .y = 1 + (i * cell_size),
                .w = cell_size,
                .h = cell_size,
            };
            row.push_back(cell);
        }
        cells.push_back(row);
    }
}

int Window::init_win(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Create window and renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "Conway Grid");

    return 0;
}

int Window::update(const std::vector<std::pair<int,int>>& active_cells) {
    // Draw grid background.
    SDL_SetRenderDrawColor(renderer, background.r, background.g,
                            background.b, background.a);
    SDL_RenderClear(renderer);

    // Draw grid lines.
    SDL_SetRenderDrawColor(renderer, line.r, line.g,
                            line.b, line.a);

    for (int x = 0; x < 1 + cell_width * cell_size; x += cell_size) {
        SDL_RenderDrawLine(renderer, x, 0, x, window_height);
    }

    for (int y = 0; y < 1 + cell_height * cell_size; y += cell_size) {
        SDL_RenderDrawLine(renderer, 0, y, window_width, y);
    }

    // Draw grid cursor.
    SDL_SetRenderDrawColor(renderer, active.r,
                            active.g, active.b,
                            active.a);
    
    for (const std::pair<int,int>& active_cell : active_cells) {
        if (active_cell.first >= cell_width || active_cell.first < 0) continue;
        if (active_cell.second >= cell_height || active_cell.second < 0) continue;
        SDL_RenderFillRect(renderer, &cells[active_cell.second][active_cell.first]);
    }

    SDL_RenderPresent(renderer);

    return 0;
}

int Window::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}