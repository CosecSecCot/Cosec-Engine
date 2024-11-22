#include "Game.hpp"
#include "EntityComponentSystem/Components/AnimationComponent.hpp"
#include "EntityComponentSystem/Components/ColliderComponent.hpp"
#include "EntityComponentSystem/Components/KeyboardInput.hpp"
#include "EntityComponentSystem/Components/TextureComponent.hpp"
#include "EntityComponentSystem/Components/TransformComponent.hpp"
#include "EntityComponentSystem/ECS.hpp"
#include "EntityComponentSystem/Entity.hpp"
#include "SDL_image.h"
#include "TileMap.hpp"

#include <cassert>
#include <iostream>
#include <vector>

TileMap *tileMap;

ECS ecs;
Entity &tree = ecs.addEntity();

Entity &player = ecs.addEntity();

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 0, 0};

std::vector<Entity *> Game::colliders;

bool Game::renderDebug = false;

Game::Game() {
    this->isRunning = false;
    this->window = nullptr;
}

Game::~Game() {
    this->clean();
}

void Game::init(const std::string &title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    int sdlWindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
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
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

    auto &playerTransform = player.addComponent<TransformComponent>(22 * 16 * 2, 4 * 16 * 2, 24, 24);
    playerTransform.scale = 2;
    auto &playerTexture =
        player.addComponent<TextureComponent>("assets/player/player.png", playerTransform, 0, 0, Vector2D(0.5, 0.85));
    player.addComponent<ColliderComponent>(playerTransform, 8, 2, 8, 20);

    auto &playerAnimation = player.addComponent<AnimationComponent>(playerTexture);

    // Idle Animations
    auto playerIdleDown = Animation{0, 5, 100};
    auto playerIdleBottomDiagonal = Animation{1, 5, 100};
    auto playerIdleSide = Animation{2, 5, 100};
    auto playerIdleTopDiagonal = Animation{3, 5, 100};
    auto playerIdleUp = Animation{4, 5, 100};
    playerAnimation.addAnimation("idleDown", playerIdleDown);
    playerAnimation.addAnimation("idleBottomDiagonal", playerIdleBottomDiagonal);
    playerAnimation.addAnimation("idleSide", playerIdleSide);
    playerAnimation.addAnimation("idleTopDiagonal", playerIdleTopDiagonal);
    playerAnimation.addAnimation("idleUp", playerIdleUp);

    // Walk Animations
    auto playerWalkDown = Animation{5, 3, 75};
    auto playerWalkBottomDiagonal = Animation{6, 3, 75};
    auto playerWalkSide = Animation{7, 3, 75};
    auto playerWalkTopDiagonal = Animation{8, 3, 75};
    auto playerWalkUp = Animation{9, 3, 75};
    playerAnimation.addAnimation("walkDown", playerWalkDown);
    playerAnimation.addAnimation("walkBottomDiagonal", playerWalkBottomDiagonal);
    playerAnimation.addAnimation("walkSide", playerWalkSide);
    playerAnimation.addAnimation("walkTopDiagonal", playerWalkTopDiagonal);
    playerAnimation.addAnimation("walkUp", playerWalkUp);

    player.addComponent<KeyboardInput>(playerTransform, playerAnimation);

    auto &treeTransform = tree.addComponent<TransformComponent>(23 * 16 * 2, 1 * 16 * 2, 80, 112);
    treeTransform.scale = 2;
    tree.addComponent<TextureComponent>("assets/tiles/seasonal sample (autumn).png", treeTransform, 176, 0,
                                        Vector2D(0.5, 0.86));
    tree.addComponent<ColliderComponent>(treeTransform, 16, 16, 32, 96);
    Game::colliders.push_back(&tree);

    if (player.hasComponents<TransformComponent, TextureComponent, KeyboardInput, ColliderComponent,
                             AnimationComponent>()) {
        std::cout << "[INFO] Player has been initialized." << '\n';
    } else {
        std::cout << "[ERROR] Player doesn't have all the components." << '\n';
        exit(1);
    }

    tileMap = new TileMap("assets/tiles/untitled.json");
}

void Game::handleEvents() {
    SDL_PollEvent(&Game::event);

    switch (Game::event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update() {
    ecs.update();

    auto playerTransform = player.getComponent<TransformComponent>();

    SDL_GetWindowSize(Game::window, &Game::camera.w, &Game::camera.h);

    camera.x += (static_cast<int>(playerTransform->position.x) - (camera.w / 2) +
                 (playerTransform->width * playerTransform->scale / 2) - camera.x) /
                10;
    camera.y += (static_cast<int>(playerTransform->position.y) - (camera.h / 2) +
                 (playerTransform->height * playerTransform->scale / 2) - camera.y) /
                10;

    camera.x = std::max(camera.x, 0);
    camera.x = std::min(camera.x, (2 * tileMap->width * tileMap->tileSize) - camera.w);
    camera.y = std::max(camera.y, 0);
    camera.y = std::min(camera.y, (2 * tileMap->height * tileMap->tileSize) - camera.h);

    // std::cout << "Camera: " << camera.x << ' ' << camera.y << ' ' << camera.w << ' ' << camera.h << '\n';

    for (auto collider : Game::colliders) {
        player.resolveStaticCollision(*collider);
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);

    tileMap->render();
    ecs.render();

    player.getComponent<TextureComponent>()->debug();
    player.getComponent<ColliderComponent>()->debug();
    for (auto collider : Game::colliders) {
        collider->getComponent<TextureComponent>()->debug();
        collider->getComponent<ColliderComponent>()->debug();
    }

    SDL_RenderPresent(Game::renderer);
}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
    std::cerr << "[INFO] Game cleaned!" << '\n';
}
