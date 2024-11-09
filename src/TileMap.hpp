#ifndef TileMap_hpp
#define TileMap_hpp
#pragma once

#include "SDL.h"

#include <map>
#include <vector>

enum class TileType : uint8_t {
    DIRT,
    GRASS,
    WATER
};

struct Tile {
    TileType type;
    int variant;
    int xPos;
    int yPos;
};

class TileMap {
public:
    explicit TileMap(int tileSize);
    ~TileMap();

    void render();

private:
    int tileSize;
    std::vector<Tile> tiles; // The tile objects that are going to be rendered on the screen.

    SDL_Texture *tileSheet;                              // The tiles sprite-sheet
    std::map<TileType, std::vector<SDL_Rect>> tileRects; // position of the individual tiles in the spriteSheet
};

#endif /* TileMap.hpp */
