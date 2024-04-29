#ifndef SDL_WINDOW_1234
#define SDL_WINDOW_1234
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <iostream>

#if __APPLE__
    #include <CoreGraphics/CoreGraphics.h>
    extern CGDirectDisplayID mainDisplayId;
#endif

extern size_t screenHeight;
extern size_t screenWidth;

class Window {
public:
    Window(int cell_w, int cell_h, const char* title);
    ~Window();
    int update(const std::vector<std::pair<int,int>>& active_cells);
    int destroy();
    void handleMouse(int32_t x, int32_t y);
    bool get_mouse_state();
    void set_mouse_state(bool toggle);
private:
    int cell_width, cell_height, cell_size, window_width, window_height;
    bool mouse_hover = true;
    std::vector<std::vector<SDL_Rect>> cells;
    SDL_Rect        ghost;
    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_Color       background    =  {22, 22, 22, 255};      // Barely Black
    SDL_Color       line          =  {44, 44, 44, 255};      // Dark grey
    SDL_Color       active        =  {255, 255, 255, 255};   // White
    SDL_Color       ghost_color   =  {44, 44, 44, 255};

    int init_win(int width, int height, const char* title);
};

#endif