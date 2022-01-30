#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <gametest/SpriteNode.hpp>
#include <gametest/Category.hpp>

SpriteNode::SpriteNode(const sf::Texture &texture)
        : mSprite(texture) {}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &rect): mSprite(texture, rect) {}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}
