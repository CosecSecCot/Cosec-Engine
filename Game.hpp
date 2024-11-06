#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Game {
public:
    Game();
    ~Game();

    void init(const std::string title, int x_pos, int y_pos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    inline bool running() {
        return isRunning;
    }

private:
    bool isRunning;

    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif
