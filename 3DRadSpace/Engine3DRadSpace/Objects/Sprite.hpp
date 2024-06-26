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
		Sprite(const std::string &name, bool visible, const std::string &path, const Math::Vector2& pos, const Math::Vector2& scale, float depth = 0.0,
			const Math::Vector2& pivot = Math::Vector2::Zero(), float rotation = 0.0f, bool flipU = false, bool flipV = false,
			const Color& tintColor = Colors::White);

		Sprite(const std::string &name, bool visible, RefTexture2D resource, const Math::Vector2 &pos, const Math::Vector2& scale, float depth = 0.0,
			const Math::Vector2 &pivot = Math::Vector2::Zero(), float rotation = 0.0f, bool flipU = false, bool flipV = false,
			const Color &tintColor = Colors::White);

		bool FlipU;
		bool FlipV;

		RefTexture2D Image;
		Graphics::Texture2D *GetSpriteImage();

		Color TintColor;

		void Initialize() override;
		void Load(Content::ContentManager *content) override;
		void Load(Content::ContentManager* content, const std::filesystem::path& path) override;
		void Update(Input::Keyboard &keyboard, Input::Mouse &mouse, double dt) override;
		void Draw(Graphics::SpriteBatch *spriteBatch, double dt) override;

		void EditorInitialize() override;
		void EditorLoad(Content::ContentManager *content) override;
		void EditorDraw(Graphics::SpriteBatch *spriteBatch, double dt, bool selected) override;
		Reflection::UUID GetUUID() const noexcept override;

		virtual ~Sprite() = default;
	};
}

REFL_FWD(Sprite)