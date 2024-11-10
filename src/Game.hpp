#ifndef Game_hpp
#define Game_hpp
#pragma once

#include "SDL.h"
#include <string>

class Game {
public:
    static const int FPS = 60;
    static const int expectedFrameTime = 1000 / FPS;

    static SDL_Renderer *renderer;
    static SDL_Event event;

    Game();
    ~Game();

    void init(const std::string &title, int x_pos, int y_pos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    [[nodiscard]] bool running() const {
        return isRunning;
    }

private:
    bool isRunning;

    SDL_Window *window;
};

#endif /* Game.hpp */
