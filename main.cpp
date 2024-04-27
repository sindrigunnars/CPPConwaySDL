#include "src/window.h"
#include <SDL2/SDL.h>

int main(void) {
    Window win(21, 11, 30);
    int quit = 0;
    std::vector<std::pair<int,int>> empty;
    while (!quit) {
        empty.push_back(std::pair<int,int>(rand() % 21,rand() % 11));
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = SDL_TRUE;
                break;
            }
        }
        win.update(empty);
        SDL_Delay(200);
        empty.clear();
    }
    win.destroy();
    return 0;
}