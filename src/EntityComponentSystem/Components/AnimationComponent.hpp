#pragma once

#include "EntityComponentSystem/Component.hpp"
#include "EntityComponentSystem/Components/TextureComponent.hpp"

// The animation of an entity requires a TextureComponent
// which has image consisting of all the animations
// It is required that each row of the image is
// a reserved of a unique animation.
struct Animation {
    int index;  // The index of the row in the texture
    int frames; // How many frames does the animation has
    int delay;  // How much delay is between each frame of the animation
};

class AnimationComponent : public Component {
public:
    AnimationComponent() = delete;

    // A TextureComponent is required to loop over animations
    // of an entitiy
    explicit AnimationComponent(TextureComponent &texture)
        : texture(&texture), index(0), frames(0), delay(std::numeric_limits<int>::max()) {}

    // Adds the animation to the animations map
    // with the corresponding name
    void addAnimation(const std::string &name, const Animation &animation) {
        if (animations.find(name) == animations.end()) {
            animations[name] = animation; // Store a copy
            std::cout << "Created Animation \"" << name << "\" with index: " << animation.index
                      << ", frames: " << animation.frames << ", delay: " << animation.delay << '\n';
        } else {
            std::cout << "[WARNING] Couldn't add Animation \"" << name << "\", it already exists!\n";
        }
    }

    void play(const std::string &name) {
        auto it = animations.find(name);
        if (it == animations.end()) {
            std::cout << "[ERROR] Animation \"" << name << "\" not found!\n";
            return;
        }

        const Animation &animation = it->second;
        this->index = animation.index;
        this->frames = animation.frames;
        this->delay = animation.delay;
    }

    void update() override {
        if (animations.empty() || (frames == 0)) {
            return;
        }

        // set the row of the animation
        texture->srcRect.y = this->index * texture->srcRect.h;

        // Loop over images in the src texture
        // starting from the very x = 0 to x = (frames - 1)
        texture->srcRect.x = static_cast<int>((SDL_GetTicks() / delay) % frames) * texture->srcRect.w;
    }

private:
    TextureComponent *texture;
    std::map<std::string, Animation> animations;
    int index, frames, delay;
};
