#pragma once

#include "BasicTypes.hpp"

namespace engine
{
    class Voxel
    {
    public:
        Voxel();
        ~Voxel() = default;
        Color color;
        bool active;
        unsigned type;
        bool isForced;
    };
}