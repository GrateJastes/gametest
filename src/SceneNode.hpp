#pragma once


#include <memory>
#include <vector>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>

class SceneNode: public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode> NodePtr;

public:
    SceneNode();

    void attachChild(NodePtr child);
    NodePtr detachChild(const SceneNode &node);

    void update(sf::Time dt);

    sf::Transform getWorldTransform() const;
    const sf::Vector2f getWorldPosition() const;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override final;

    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {};
    void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

    virtual void updateCurrent(sf::Time dt) {}
    void updateChildren(sf::Time dt);

private:
    std::vector<NodePtr> mChildren;
    SceneNode *mParent;
};


