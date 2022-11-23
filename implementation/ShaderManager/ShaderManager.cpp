#include "ShaderManager.hpp"

namespace engine
{
    namespace implementation
    {
        const engine::Shader ShaderManager::createShader(ShaderType type)
        {
            this->shaders.push_back(std::move(Shader(type)));
            return --this->shaders.end();
        }

        const engine::Shader ShaderManager::createShader(ShaderType type, const ShaderSource& path)
        {
            Shader shader(type, path);
            this->shaders.push_back(std::move(shader));
            return --this->shaders.end();
        }

        void ShaderManager::loadShader(const engine::Shader& shader, const ShaderSource& path)
        {
            auto iterator = this->shaders.begin();
            for (; iterator != this->shaders.end(); iterator++)
                if (iterator == shader)
                    break;

            if (iterator != this->shaders.end())
                iterator->compile(path);
        }

        void ShaderManager::deleteShader(const engine::Shader iterator)
        {
            this->shaders.erase(iterator);
        }

        void ShaderManager::deleteShaders()
        {
            this->shaders.clear();
        }


    }
}