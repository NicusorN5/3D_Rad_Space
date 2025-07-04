#pragma once
#include "IObject.hpp"
#include "..\Reflection\Reflection.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class LinearPixelFogEffect;
}

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// This object controls the Fog effect.
	/// </summary>
	class E3DRSP_OBJECTS_EXPORT Fog: public IObject
	{
	protected:
		::Engine3DRadSpace::Graphics::Rendering::LinearPixelFogEffect* _effect;
	public:
		Fog();
		explicit Fog(const std::string& name, bool enabled, float begin, float end, Math::Color color);

		float FogBegin;
		float FogEnd;
		Math::Color FogColor;

		Fog(const Fog&) = default;
		Fog(Fog&&) = default;
		Fog& operator=(const Fog&) = default;
		Fog& operator=(Fog&&) = default;

		void Initialize() override;

		void Load() override;
		void Load(const std::filesystem::path& path) override;

		void Update() override;

		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~Fog() = default;
	};
}

REFL_FWD(Fog)