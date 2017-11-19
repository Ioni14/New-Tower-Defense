#pragma once

#include <SFML/Graphics/Shader.hpp>
#include <unordered_map>
#include <memory>

class ShaderManager
{
public:
    using ShaderUPtr = std::unique_ptr<sf::Shader>;

    enum class ID { ENTITY };

    ShaderManager();

    void load(ID id, const std::string& filename, sf::Shader::Type type);
    void loadMultiple(ID id, const std::string& vertFilename, const std::string& fragFilename);
    sf::Shader& get(ID id);

private:
    std::unordered_map<ID, ShaderUPtr> mShaders;
};
