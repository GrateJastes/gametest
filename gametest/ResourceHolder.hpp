#pragma once

#include <map>
#include <memory>
#include <gametest/Textures.hpp>
#include <gametest/Fonts.hpp>
#include <SFML/Graphics/Font.hpp>


template<typename Resource, typename Identifier>
class ResourceHolder {
public:
    void load(Identifier id, const std::string &filename);

    template<typename Parameter>
    void load(Identifier id, const std::string &filename, const Parameter &secondParam);

    Resource &get(Identifier id);

    const Resource &get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include <gametest/ResourceHolder.inl>


typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>       FontHolder;
