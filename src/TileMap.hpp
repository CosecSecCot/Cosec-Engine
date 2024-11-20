#ifndef TileMap_hpp
#define TileMap_hpp
#pragma once

#include "SDL.h"
#include "TextureManager.hpp"
#include "Utils/Vector2D.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <fstream>
#include <map>

struct Tile {
    int id;
    int xPos;
    int yPos;
};

class TileMap {
public:
    explicit TileMap(const std::string &path);
    ~TileMap();

    void render();

private:
    int tileSize;

    SDL_Texture *tileSet;              // The tileset
    std::map<int, SDL_Rect> tileRects; // src rects of the tiles in tileset (tileID -> SDL_Rect)
    std::map<Vector2D, Tile> tiles;    // The tile objects that are going to be rendered on the screen.

    int loadTileSet(const std::string &path) {
        std::cout << "LOADING " << path << " ...\n";

        std::ifstream file(path);
        json data = json::parse(file);

        std::string tileSetImageLocation = "assets/tiles/" + data["image"].get<std::string>();
        this->tileSet = TextureManager::loadTexture(tileSetImageLocation);

        int _tileWidth = data["tilewidth"].get<int>();
        int _tileHeight = data["tileheight"].get<int>();
        int imageWidth = data["imagewidth"].get<int>();
        int imageHeight = data["imageheight"].get<int>();

        printf("tileWidth: %d\ntileHeight: %d\nimageWidth: %d\nimageHeight: %d\n", _tileWidth, _tileHeight, imageWidth,
               imageHeight);

        for (int row = 0; row < imageHeight / _tileHeight; row++) {
            for (int col = 0; col < imageWidth / _tileWidth; col++) {
                int tileID = ((imageWidth / _tileWidth) * row) + col;
                printf("tileId:%d - (%d, %d)\n", tileID, col * _tileWidth, row * _tileHeight);
                this->tileRects[tileID] = SDL_Rect{col * _tileWidth, row * _tileHeight, _tileWidth, _tileHeight};
            }
        }

        return 0;
    }

    int loadMap(const std::string &path) {
        std::ifstream file(path);
        json data = json::parse(file);

        std::string tileSetFileLocation = "assets/tiles/" + data["tilesets"][0]["source"].get<std::string>();
        std::cout << "Loading Tileset : \"" << tileSetFileLocation << "\"\n";
        loadTileSet(tileSetFileLocation);

        std::cout << "Loading TileMap...\n";

        this->tileSize = data["tileheight"].get<int>();

        int mapWidth = data["width"].get<int>();
        int mapHeight = data["height"].get<int>();

        printf("tilesize: %d\nmapWidth: %d\nmapHeight: %d\n", tileSize, mapWidth, mapHeight);

        for (int row = 0; row < mapHeight; row++) {
            for (int col = 0; col < mapWidth; col++) {
                // std::cout << "Getting (" << row << ", " << col << ")\n";
                int tileID = data["layers"][0]["data"][(mapWidth * row) + col].get<int>() - 1;
                this->tiles[Vector2D(col, row)] = Tile{tileID, col, row};
            }
        }

        return 0;
    }
};

#endif /* TileMap.hpp */
