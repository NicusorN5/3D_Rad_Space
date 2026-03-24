#pragma once
#include <Engine3DRadSpace/Games/Game.hpp>

namespace Engine3DRadSpace::Objects
{
	class Camera;
	class Skinmesh;
}

class SkinmeshPreviewer : public Engine3DRadSpace::Game
{
	Engine3DRadSpace::Objects::Camera* _camera;
	Engine3DRadSpace::Objects::Skinmesh* _skinmesh;
	float _zoom;
	float _initialZoom;
	Engine3DRadSpace::Math::Vector2 _camCoords;
public:
	explicit SkinmeshPreviewer(const std::filesystem::path& modelPath);

	SkinmeshPreviewer(SkinmeshPreviewer &) = delete;
	SkinmeshPreviewer &operator=(SkinmeshPreviewer &) = delete;

	void Load() override;
	void Update() override;
};

