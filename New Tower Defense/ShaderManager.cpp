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

void ShaderManager::loadMultiple(ID id, const std::string& vertFilename, const std::string& fragFilename)
{
    ShaderUPtr shader = std::make_unique<sf::Shader>();
    shader->loadFromFile(vertFilename, fragFilename);
    mShaders.insert({ id, std::move(shader) });
}

sf::Shader& ShaderManager::get(ID id)
{
    auto& it = mShaders.find(id);
    if (it == mShaders.end() || it->second == nullptr) {
        throw std::logic_error("The shader does not exist.");
    }

    return *(it->second);
}
