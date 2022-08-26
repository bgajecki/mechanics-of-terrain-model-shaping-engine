#include "ShaderLoader.hpp"

namespace Engine
{
    ShaderLoader::ShaderLoader(const ShaderList& list)
        : shaders(list)
    {

    }

    const size_t ShaderLoader::addShader(const ShaderData& shader)
    {
        this->shaders.push_back(shader);
        size_t index = this->shaders.size() - 1u;
        return index;
    }

    void ShaderLoader::deleteShader(const size_t index)
    {
        this->shaders.erase(this->shaders.begin() + index);
    }

    ShaderDataPointer ShaderLoader::getShaderData(const size_t index)
    {
        ShaderDataPointer data = std::make_unique<ShaderData>(this->shaders[index]);
        std::string path = data->source;
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

        data->source = stream.str().c_str();
        return data;
    }
}