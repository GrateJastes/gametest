#include "SceneNode.hpp"

SceneNode::SceneNode() : mChildren(), mParent(nullptr) {}

SceneNode::NodePtr SceneNode::detachChild(const SceneNode &node) {
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (NodePtr &p) -> bool {
        return p.get() == &node;
    });

    NodePtr result = std::move(*found);
    result->mParent = nullptr;

    mChildren.erase(found);
    return result;
}

void SceneNode::attachChild(SceneNode::NodePtr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &child : mChildren) {
        child->draw(target, states);
    }
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateChildren(sf::Time dt) {
    for (auto &child : mChildren) {
        child->update(dt);
    }
}

sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode *node = this; node != nullptr; node = node->mParent) {
        transform = node->getTransform() * transform;
    }

    return transform;
}

const sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}
