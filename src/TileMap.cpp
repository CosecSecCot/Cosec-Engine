#include "TileMap.hpp"
#include "Game.hpp"

#define UPSCALE_FACTOR 2

TileMap::TileMap(const std::string &path) {
    loadMap("assets/tiles/untitled.json");
}

TileMap::~TileMap() {
    SDL_DestroyTexture(this->tileSet);
}

void TileMap::render() {
    assert(Game::renderer != nullptr && "Renderer cannot be null.");

    for (auto &[pos, tile] : tiles) {
        SDL_Rect dest = {tile.xPos * tileSize * UPSCALE_FACTOR, tile.yPos * tileSize * UPSCALE_FACTOR,
                         tileSize * UPSCALE_FACTOR, tileSize * UPSCALE_FACTOR};
        SDL_RenderCopy(Game::renderer, this->tileSet, &tileRects[tile.id], &dest);
    }
}
