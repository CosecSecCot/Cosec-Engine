#include "Game.hpp"
#include "Utils/LTimer.hpp"
#include <iostream>

Game *game = nullptr;

int main() {
    game = new Game();
    game->init("Top Down Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 675, false);
    // Game::renderDebug = true;

    Uint32 frameStart;
    Uint32 frameTime;

    LTimer fpsTimer, capTimer;
    int countedFrames = 0;
    fpsTimer.start();

    while (game->running()) {
        capTimer.start();

        // Calculate and correct fps
        float avgFPS = static_cast<float>(countedFrames) / (static_cast<float>(fpsTimer.getTicks()) / 1000.f);
        if (avgFPS > 2000000) {
            avgFPS = 0;
        }

        std::cout << "Avg FPS: " << avgFPS << '\n';

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (Game::expectedFrameTime > frameTime) {
            SDL_Delay(Game::expectedFrameTime - frameTime);
        }

        Uint32 frameTicks = capTimer.getTicks();
        if (std::isless(frameTicks, Game::expectedFrameTime)) {
            SDL_Delay(Game::expectedFrameTime - frameTicks);
        }
        countedFrames++;
    }

    delete game;

    return 0;
}
