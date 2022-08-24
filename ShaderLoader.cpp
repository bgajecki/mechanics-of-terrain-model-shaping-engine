#include "ShaderLoader.hpp"

namespace Engine
{
    const ShaderList::iterator ShaderLoader::addShader(const ShaderData& shader)
    {
        this->shaders.push_back(shader);
        size_t index = this->shaders.size() - 1u;
        return index;
    }

    void ShaderLoader::deleteShader(size_t iterator)
    {
        this->shaders.erase(this->shaders.begin() + iterator);
    }

    const ShaderData& ShaderLoader::getShaderData(const size_t index)
    {
        ShaderData data = this->shaders[index];
        std::string path = data.source;
        std::ifstream file(path);
        std::stringstream stream;

        if (!file.is_open())
        {
            DEBUG(std::cerr << "Could not read file " << path << ". File does not exist." << std::endl);
            stream << "";
        }
        else
        {
            stream << file.rdbuf();
        }

        data.source = stream.str().c_str();
        return data;
    }
}