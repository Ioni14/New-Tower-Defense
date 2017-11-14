#pragma once

#include <SFML/Graphics/Shader.hpp>
#include <unordered_map>
#include <memory>

class ShaderManager
{
public:
    using ShaderUPtr = std::unique_ptr<sf::Shader>;

    enum class ID { BASIC_VERT, BASIC_FRAG };

    ShaderManager();

    void load(ID id, const std::string& filename, sf::Shader::Type type);
    const sf::Shader& get(ID id) const;

private:
    std::unordered_map<ID, ShaderUPtr> mShaders;
};
