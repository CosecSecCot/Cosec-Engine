#ifndef TileMap_hpp
#define TileMap_hpp
#pragma once

#include "SDL.h"
#include "Utils/Vector2D.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <fstream>
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

    SDL_Texture *tileSheet;                              // The tiles sprite-sheet
    std::map<TileType, std::vector<SDL_Rect>> tileRects; // Variants of a specific TileType (their src rects)
    std::map<Vector2D, Tile> tiles; // The tile objects that are going to be rendered on the screen.

    static int loadMap(const std::string &path) {
        std::ifstream file(path);
        json data = json::parse(file);

        std::cout << data << '\n';

        return 0;
    }
};

#endif /* TileMap.hpp */
