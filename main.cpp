#include "Game.hpp"

Game *game = nullptr;

int main() {
    game = new Game();
    game->init("Top Down Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    Uint32 frameStart;
    Uint32 frameTime;

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (Game::expectedFrameTime > frameTime) {
            SDL_Delay(Game::expectedFrameTime - frameTime);
        }
    }

    delete game;

    return 0;
}
