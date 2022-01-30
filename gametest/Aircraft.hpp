#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <gametest/Entity.hpp>
#include <gametest/ResourceHolder.hpp>

class Aircraft : public Entity {
public:
    enum class Type {
        EAGLE,
        RAPTOR,
    };

public:
    explicit Aircraft(Type type, const TextureHolder &textures);

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Type       mType;
    sf::Sprite mSprite;

    unsigned int getCategory() const override;
};
