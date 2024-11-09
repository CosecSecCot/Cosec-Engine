#include "TileMap.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

#define UPSCALE_FACTOR 2

TileMap::TileMap(int tileSize) : tileSize(tileSize) {
    this->tileSheet = TextureManager::loadTexture("assets/tiles/seasonal sample (autumn).png");

    this->tileRects[TileType::GRASS] = {
        SDL_Rect{0, 16, tileSize, tileSize}, // Variant: 1
        SDL_Rect{0, 32, tileSize, tileSize}, // Variant: 2
        SDL_Rect{0, 48, tileSize, tileSize}, // Variant: 3
        SDL_Rect{0, 64, tileSize, tileSize}, // Variant: 4
        SDL_Rect{0, 80, tileSize, tileSize}, // Variant: 5
    };

    this->tileRects[TileType::DIRT] = {
        SDL_Rect{64, 0, tileSize, tileSize},  // Variant: 1
        SDL_Rect{64, 16, tileSize, tileSize}, // Variant: 2
        SDL_Rect{64, 32, tileSize, tileSize}, // Variant: 3
        SDL_Rect{64, 48, tileSize, tileSize}, // Variant: 4
        SDL_Rect{64, 64, tileSize, tileSize}, // Variant: 5
    };

    this->tileRects[TileType::WATER] = {
        SDL_Rect{176, 208, tileSize, tileSize}, // Variant: 1
        SDL_Rect{192, 208, tileSize, tileSize}, // Variant: 2
        SDL_Rect{208, 208, tileSize, tileSize}, // Variant: 3 (darker)
        SDL_Rect{176, 224, tileSize, tileSize}, // Variant: 4
        SDL_Rect{192, 224, tileSize, tileSize}, // Variant: 5
        SDL_Rect{208, 224, tileSize, tileSize}, // Variant: 6
    };

    // Try Load from a file
    tiles.push_back(Tile{TileType::GRASS, 1, 0, 0});
    tiles.push_back(Tile{TileType::GRASS, 2, 1, 0});
    tiles.push_back(Tile{TileType::GRASS, 1, 2, 0});
    tiles.push_back(Tile{TileType::DIRT, 1, 0, 1});
    tiles.push_back(Tile{TileType::DIRT, 2, 1, 1});
    tiles.push_back(Tile{TileType::DIRT, 1, 2, 1});
    tiles.push_back(Tile{TileType::WATER, 1, 0, 2});
    tiles.push_back(Tile{TileType::WATER, 2, 1, 2});
    tiles.push_back(Tile{TileType::WATER, 1, 2, 2});
}

void TileMap::render() {
    for (Tile tile : tiles) {
        SDL_Rect dest = {tile.xPos * tileSize * UPSCALE_FACTOR, tile.yPos * tileSize * UPSCALE_FACTOR,
                         tileSize * UPSCALE_FACTOR, tileSize * UPSCALE_FACTOR};
        SDL_RenderCopy(Game::renderer, this->tileSheet, &tileRects[tile.type][tile.variant], &dest);
    }
}
