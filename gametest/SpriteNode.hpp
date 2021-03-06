#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <gametest/SceneNode.hpp>

class SpriteNode : public SceneNode {
public:
    explicit SpriteNode(const sf::Texture &texture);

    SpriteNode(const sf::Texture &texture, const sf::IntRect &rect);

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
};


