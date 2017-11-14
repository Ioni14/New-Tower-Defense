#include "TextureManager.h"

TextureManager::TextureManager() :
	mTextures()
{
}

void TextureManager::load(ID id, const std::string & filename)
{
    TextureUPtr tex = std::make_unique<sf::Texture>();
    tex->loadFromFile(filename); // texture is blank if false
    mTextures.insert({ id, std::move(tex) });
}

const sf::Texture & TextureManager::get(ID id) const
{
    const auto& it = mTextures.find(id);
    if (it == mTextures.end() || it->second == nullptr) {
        throw std::logic_error("The texture does not exist.");
    }

    return *(it->second);
}
