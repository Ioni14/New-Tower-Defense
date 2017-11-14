#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>

class TextureManager
{
public:
    using TextureUPtr = std::unique_ptr<sf::Texture>;

    enum class ID { PLAYER_SPRITESHEET, TILESET }; // TODO : merge all entities into a large spritesheet ? divide by topic/layer ?

	TextureManager();

    void load(ID id, const std::string& filename);
	const sf::Texture& get(ID id) const;

private:
	std::unordered_map<ID, TextureUPtr> mTextures;
};
