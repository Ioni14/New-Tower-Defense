#include "ShaderManager.h"

ShaderManager::ShaderManager() :
    mShaders()
{
}

void ShaderManager::load(ID id, const std::string & filename, sf::Shader::Type type)
{
    ShaderUPtr shader = std::make_unique<sf::Shader>();
    shader->loadFromFile(filename, type);
    mShaders.insert({ id, std::move(shader) });
}

const sf::Shader& ShaderManager::get(ID id) const
{
    const auto& it = mShaders.find(id);
    if (it == mShaders.end() || it->second == nullptr) {
        throw std::logic_error("The shader does not exist.");
    }

    return *(it->second);
}
