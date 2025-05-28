#pragma once
#include "../IObject2D.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	using RefTexture2D = Content::AssetID<Graphics::Texture2D>;

	class DLLEXPORT Sprite : public IObject2D
	{
		Graphics::Texture2D *_texture;
		std::unique_ptr<std::string> _tempResourceString;
	public:
		Sprite();
		Sprite(
			const std::string &name,
			bool visible,
			const std::string &path, 
			const Math::Vector2& pos,
			const Math::Vector2& scale, 
			float depth = 0.0,
			const Math::Vector2& pivot = Math::Vector2::Zero(),
			float rotation = 0.0f,
			bool flipU = false,
			bool flipV = false,
			const Color& tintColor = Colors::White
		);

		Sprite(
			const std::string &name,
			bool visible,
			RefTexture2D resource, 
			const Math::Vector2 &pos,
			const Math::Vector2& scale,
			float depth = 0.0,
			const Math::Vector2 &pivot = Math::Vector2::Zero(),
			float rotation = 0.0f,
			bool flipU = false,
			bool flipV = false,
			const Color &tintColor = Colors::White
		);

		bool FlipU;
		bool FlipV;

		RefTexture2D Image;
		Graphics::Texture2D *GetSpriteImage();

		Color TintColor;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;
		void Draw2D() override;

		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		virtual ~Sprite() = default;
	};
}

REFL_FWD(Sprite)