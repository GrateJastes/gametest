#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Entity.hpp"
#include "ResourceHolder.hpp"

class Aircraft: public Entity {
public:
    enum class Type {
        EAGLE,
        RAPTOR,
    };

public:
    explicit Aircraft(Type type, const TextureHolder &textures);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Type mType;
    sf::Sprite mSprite;
};
