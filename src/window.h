#ifndef SDL_WINDOW_1234
#define SDL_WINDOW_1234
#include <SDL2/SDL.h>
#include <vector>

class Window {
public:
    Window(int cell_w, int cell_h, int cell_s);
    int update(const std::vector<std::pair<int,int>>& active_cells);
    int destroy();
private:
    int cell_width, cell_height, cell_size, window_width, window_height;
    std::vector<std::vector<SDL_Rect>> cells;
    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_Color       background    =  {22, 22, 22, 255};      // Barely Black
    SDL_Color       line          =  {44, 44, 44, 255};      // Dark grey
    SDL_Color       active        =  {255, 255, 255, 255};   // White

    int init_win(int width, int height);
};

#endif