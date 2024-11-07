#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include <string>

class Game {
public:
    static const int FPS = 60;
    static const int expectedFrameTime = 1000 / FPS;

    Game();
    ~Game();

    void init(std::string title, int x_pos, int y_pos, int width, int height, bool fullscreen);

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
    SDL_Renderer *renderer;
};

#endif
