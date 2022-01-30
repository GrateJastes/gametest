#pragma once


#include <SFML/System/Vector2.hpp>
#include <gametest/SceneNode.hpp>

class Entity : public SceneNode {
public:
    void setVelocity(sf::Vector2f velocity);

    void setVelocity(float vx, float vy);

    sf::Vector2f getVelocity() const;

    void accelerate(sf::Vector2f acceleration);

    void accelerate(float dx, float dy);

private:
    sf::Vector2f mVelocity;

private:
    void updateCurrent(sf::Time dt) override;
};


