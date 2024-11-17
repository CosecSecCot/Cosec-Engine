#include "TileMap.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

#define UPSCALE_FACTOR 2

#define RANDOM_VARIANT(type) static_cast<int>(rand() % this->tileRects[(type)].size())
#define ADD_TILE(type, x, y) tiles[Vector2D((x), (y))] = Tile{(type), RANDOM_VARIANT(type), (x), (y)};

#define ADD_CONTD(type, row, start, end)                                                                               \
    for (int i = start; i <= end; i++) ADD_TILE(type, i, (row))

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
        SDL_Rect{208, 208, tileSize, tileSize}, // Variant: 3
        // SDL_Rect{176, 224, tileSize, tileSize}, // Variant: 4 (darker) // will use later
        SDL_Rect{192, 224, tileSize, tileSize}, // Variant: 5
        SDL_Rect{208, 224, tileSize, tileSize}, // Variant: 6
    };

    // Try Load from a file
    loadMap("assets/tiles/untitled.tmx");

    {
        srand(time(nullptr));

        for (int j = 0; j < 40; j++) {
            ADD_CONTD(TileType::WATER, j, 0, 49);
        }

        ADD_TILE(TileType::DIRT, 0, 0);
        ADD_CONTD(TileType::GRASS, 0, 1, 3);
        ADD_CONTD(TileType::GRASS, 0, 17, 24);

        ADD_CONTD(TileType::GRASS, 1, 0, 3);
        ADD_CONTD(TileType::GRASS, 1, 18, 24);

        ADD_CONTD(TileType::GRASS, 2, 0, 2);
        ADD_CONTD(TileType::GRASS, 2, 20, 24);

        ADD_TILE(TileType::GRASS, 0, 3);
        ADD_TILE(TileType::DIRT, 14, 3);
        ADD_TILE(TileType::DIRT, 14, 3);
        ADD_CONTD(TileType::DIRT, 3, 17, 21);
        ADD_CONTD(TileType::GRASS, 3, 18, 24);

        ADD_CONTD(TileType::DIRT, 4, 13, 17);
        ADD_CONTD(TileType::GRASS, 4, 18, 19);
        ADD_CONTD(TileType::DIRT, 4, 20, 22);
        ADD_CONTD(TileType::GRASS, 4, 23, 24);

        ADD_CONTD(TileType::DIRT, 5, 13, 14);
        ADD_CONTD(TileType::GRASS, 5, 15, 19);
        ADD_CONTD(TileType::DIRT, 5, 20, 22);
        ADD_CONTD(TileType::GRASS, 5, 23, 24);

        ADD_CONTD(TileType::DIRT, 6, 13, 14);
        ADD_CONTD(TileType::GRASS, 6, 15, 19);
        ADD_CONTD(TileType::DIRT, 6, 20, 23);
        ADD_TILE(TileType::GRASS, 24, 6);

        ADD_TILE(TileType::DIRT, 11, 7);
        ADD_CONTD(TileType::DIRT, 7, 13, 14);
        ADD_CONTD(TileType::GRASS, 7, 15, 19);
        ADD_CONTD(TileType::DIRT, 7, 20, 22);
        ADD_CONTD(TileType::GRASS, 7, 23, 24);

        ADD_CONTD(TileType::DIRT, 8, 11, 13);
        ADD_CONTD(TileType::GRASS, 8, 14, 24);

        ADD_CONTD(TileType::DIRT, 9, 11, 13);
        ADD_CONTD(TileType::GRASS, 9, 14, 24);

        ADD_CONTD(TileType::DIRT, 10, 11, 14);
        ADD_CONTD(TileType::GRASS, 10, 15, 24);

        ADD_CONTD(TileType::DIRT, 11, 12, 14);
        ADD_CONTD(TileType::GRASS, 11, 15, 24);

        ADD_CONTD(TileType::GRASS, 12, 12, 24);

        ADD_CONTD(TileType::GRASS, 13, 12, 24);

        ADD_CONTD(TileType::GRASS, 14, 12, 13);
        ADD_CONTD(TileType::DIRT, 14, 14, 17);
        ADD_CONTD(TileType::GRASS, 14, 18, 24);

        ADD_CONTD(TileType::DIRT, 15, 13, 17);
        ADD_CONTD(TileType::GRASS, 15, 18, 23);

        ADD_CONTD(TileType::DIRT, 16, 13, 18);
        ADD_CONTD(TileType::GRASS, 16, 19, 21);

        ADD_CONTD(TileType::DIRT, 17, 12, 17);

        ADD_CONTD(TileType::DIRT, 18, 13, 14);
    }
}

TileMap::~TileMap() {
    SDL_DestroyTexture(this->tileSheet);
}

void TileMap::render() {
    assert(Game::renderer != nullptr && "Renderer cannot be null.");

    for (auto &[pos, tile] : tiles) {
        SDL_Rect dest = {tile.xPos * tileSize * UPSCALE_FACTOR, tile.yPos * tileSize * UPSCALE_FACTOR,
                         tileSize * UPSCALE_FACTOR, tileSize * UPSCALE_FACTOR};
        SDL_RenderCopy(Game::renderer, this->tileSheet, &tileRects[tile.type][tile.variant], &dest);
    }
}
