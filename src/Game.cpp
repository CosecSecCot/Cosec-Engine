#include "Game.hpp"
#include "SDL_image.h"
#include <cassert>
#include <iostream>

SDL_Texture *playerTexture;
SDL_Rect playerRect;

Game::Game() {
    this->isRunning = false;
    this->window = nullptr;
    this->renderer = nullptr;
}

Game::~Game() {
    this->clean();
}

void Game::init(const std::string title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
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

    assert(this->window != nullptr);

    this->renderer = SDL_CreateRenderer(window, -1, 0);
    if (this->renderer != nullptr) {
        std::cerr << "[INFO] Renderer created!" << '\n';
    } else {
        std::cerr << "[ERROR] There was a problem creating renderer!" << '\n' << SDL_GetError();
        exit(1);
    }

    assert(this->renderer != nullptr);

    isRunning = true;

    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);

    SDL_Surface *tempPlayerSurface = IMG_Load("assets/player_animations/idle/idle_0.png");
    assert(tempPlayerSurface != nullptr);
    playerRect.w = tempPlayerSurface->w;
    playerRect.h = tempPlayerSurface->h;

    playerTexture = SDL_CreateTextureFromSurface(renderer, tempPlayerSurface);
    SDL_FreeSurface(tempPlayerSurface);
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
    playerRect.x += 1;
}

void Game::render() {
    SDL_RenderClear(this->renderer);

    SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);

    SDL_RenderPresent(this->renderer);
}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    std::cerr << "[INFO] Game cleaned!" << '\n';
}
