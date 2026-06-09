#pragma once
#include "../../Math/Color.hpp"
#include "../../Math/Vector3.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
    struct DirectionalLight
    {
        Math::Color LightColor = Math::Colors::White;
        Math::Color AmbientColor = Math::Color(0.2f, 0.2f, 0.2f, 1.0f);
        Math::Vector3 LightDirection = Math::Vector3(0.0f, -1.0f, 0.0f);
        float Intensity = 1.0f;
    };
}