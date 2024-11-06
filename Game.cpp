#include "Game.hpp"
#include "SDL_image.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_timer.h"
#include <cassert>
#include <iostream>

SDL_Texture *playerTexture;
SDL_Rect playerRect;

Game::Game() {}

Game::~Game() {}

void Game::init(const std::string title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    int sdlWindowFlags = SDL_WINDOW_SHOWN;
    if (fullscreen) {
        sdlWindowFlags |= SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cerr << "[INFO] Subsystems initialized!" << std::endl;
    } else {
        std::cerr << "[ERROR] There was a problem initializing subsystems!" << std::endl << SDL_GetError();
        exit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) != 0) {
        std::cerr << "[INFO] SDL_image initialized!" << std::endl;
    } else {
        std::cerr << "[ERROR] There was a problem initializing SDL_image!" << std::endl << SDL_GetError();
        exit(1);
    }

    this->window = SDL_CreateWindow(title.c_str(), x_pos, y_pos, width, height, sdlWindowFlags);
    if (this->window) {
        std::cerr << "[INFO] Window created!" << std::endl;
    } else {
        std::cerr << "[ERROR] There was a problem creating window!" << std::endl << SDL_GetError();
        exit(1);
    }

    assert(this->window != nullptr);

    this->renderer = SDL_CreateRenderer(window, -1, 0);
    if (this->renderer) {
        std::cerr << "[INFO] Renderer created!" << std::endl;
    } else {
        std::cerr << "[ERROR] There was a problem creating renderer!" << std::endl << SDL_GetError();
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
    SDL_Delay(200);
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
    std::cerr << "[INFO] Game cleaned!" << std::endl;
}
