#ifndef TileMap_hpp
#define TileMap_hpp
#include "Utils/Vector2D.hpp"
#include "pugixml.hpp"
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

    SDL_Texture *tileSheet;                              // The tiles sprite-sheet
    std::map<TileType, std::vector<SDL_Rect>> tileRects; // Variants of a specific TileType (their src rects)
    std::map<Vector2D, Tile> tiles; // The tile objects that are going to be rendered on the screen.

    static int loadMap(const std::string &path) {
        std::cout << "\n[INFO] Loading TileMap (" << path << ").....\n";

        pugi::xml_document doc;

        // load the XML file
        if (!doc.load_file(path.c_str()))
            return -1;

        pugi::xml_node map = doc.child("map");
        std::cout << "Tilemap Width: " << map.attribute("width").as_int() << '\n';
        std::cout << "Tilemap Height: " << map.attribute("height").as_int() << '\n';

        for (auto &layer : map.children("layer")) {
            std::cout << "Layer " << layer.attribute("id").as_int() << " - " << layer.attribute("name").as_string()
                      << '\n';

            std::string data = layer.child("data").child_value();
            auto parsedData = split(data, ",");
            for (auto &tileID : parsedData) {
                std::string id = trim(tileID);
                if (!id.empty())
                    std::cout << std::stoi(id) << ' ';
            }
            std::cout << '\n';
        }

        return 0;
    }

    static std::string trim(const std::string &str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    static std::vector<std::string> split(const std::string &str, const std::string &delim) {
        std::vector<std::string> result;

        uint64_t start = 0;
        uint64_t end = str.find(delim);
        while (end != std::string::npos) {
            std::string variant = str.substr(start, end - start);
            result.push_back(variant);
            start = end + delim.length();
            end = str.find(',', start);
        }
        result.push_back(str.substr(start));
        return result;
    }
};

#endif /* TileMap.hpp */
