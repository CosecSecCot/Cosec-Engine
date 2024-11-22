#include "TileMap.hpp"
#include "Game.hpp"

#define UPSCALE_FACTOR 2

TileMap::TileMap(const std::string &path) : width(0), height(0), tileSize(0), tileSet(nullptr) {
    if (loadMap("assets/tiles/untitled.json") != 0) {
        throw std::runtime_error("Couldn't load tilemap.\n");
    }
}

TileMap::~TileMap() {
    SDL_DestroyTexture(this->tileSet);
}

void TileMap::render() {
    assert(Game::renderer != nullptr && "Renderer cannot be null.");
    assert(tileSize != 0 && "Tilesize cannot be zero.");
    assert(tileSet != nullptr && "TileSet needs to be initalized.");

    for (auto &[pos, tile] : tiles) {
        SDL_Rect dest = {(tile.xPos * tileSize * UPSCALE_FACTOR) - Game::camera.x,
                         (tile.yPos * tileSize * UPSCALE_FACTOR) - Game::camera.y, tileSize * UPSCALE_FACTOR,
                         tileSize * UPSCALE_FACTOR};
        SDL_RenderCopy(Game::renderer, this->tileSet, &tileRects[tile.id], &dest);
    }
}
