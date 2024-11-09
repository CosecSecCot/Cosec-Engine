#include "Game.hpp"
#include "EntityComponentSystem/Components/TextureComponent.hpp"
#include "EntityComponentSystem/ECS.hpp"
#include "SDL_image.h"
#include "TileMap.hpp"

#include <cassert>
#include <iostream>

TileMap *tileMap;

ECS ecs;
Entity &player = ecs.addEntity();

SDL_Renderer *Game::renderer = nullptr;

Game::Game() {
    this->isRunning = false;
    this->window = nullptr;
}

Game::~Game() {
    this->clean();
}

void Game::init(const std::string &title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    int sdlWindowFlags = SDL_WINDOW_SHOWN;
    if (fullscreen) {
        sdlWindowFlags |= SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cerr << "[INFO] Subsystems initialized!" << '\n';
    } else {
        std::cerr << "[ERROR] There was a problem initializing subsystems!" << '\n' << SDL_GetError();
        exit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) != 0) {
        std::cerr << "[INFO] SDL_image initialized!" << '\n';
    } else {
        std::cerr << "[ERROR] There was a problem initializing SDL_image!" << '\n' << SDL_GetError();
        exit(1);
    }

    this->window = SDL_CreateWindow(title.c_str(), x_pos, y_pos, width, height, sdlWindowFlags);
    if (this->window != nullptr) {
        std::cerr << "[INFO] Window created!" << '\n';
    } else {
        std::cerr << "[ERROR] There was a problem creating window!" << '\n' << SDL_GetError();
        exit(1);
    }

    Game::renderer = SDL_CreateRenderer(window, -1, 0);
    if (Game::renderer != nullptr) {
        std::cerr << "[INFO] Renderer created!" << '\n';
    } else {
        std::cerr << "[ERROR] There was a problem creating renderer!" << '\n' << SDL_GetError();
        exit(1);
    }

    isRunning = true;

    // SDL_RenderSetLogicalSize(Game::renderer, width / 2, height / 2);
    SDL_SetRenderDrawColor(Game::renderer, 76, 61, 46, 255);

    player.addComponent<PositionComponent>(100, 0);
    {
        auto &playerPosComponent = player.getComponent<PositionComponent>();
        player.addComponent<TextureComponent>("assets/player/IDLES_5_frames.png", playerPosComponent);
    }
    if (player.hasComponents<PositionComponent, TextureComponent>()) {
        std::cout << "newPlayer has PositionComponent and TextureComponent" << '\n';
    }

    tileMap = new TileMap(16);
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update() {
    ecs.update();
    if (player.getComponent<PositionComponent>().y() > 300) {
        player.getComponent<TextureComponent>().setSrcX(24 * 10); // 11 th sprite in the current spritesheet
    }
}

void Game::render() {
    SDL_RenderClear(Game::renderer);

    tileMap->render();
    ecs.render();

    SDL_RenderPresent(Game::renderer);
}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
    std::cerr << "[INFO] Game cleaned!" << '\n';
}
