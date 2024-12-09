#pragma once
#include "../IObject2D.hpp"
#include "../Graphics/Font.hpp"
#include "../Content/AssetID.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{ 
	using RefFont = Content::AssetID<Graphics::Font>;

	class DLLEXPORT TextPrint : public IObject2D
	{
	private:
		Graphics::Font* _font = nullptr;
		std::unique_ptr<std::string> _path;
	public:
		TextPrint();
		TextPrint(
			const std::string& name, 
			bool visible,
			RefFont font,
			const std::string& text,
			const Math::Vector2& pos,
			float rotation,
			float scale, 
			Color color, 
			float depth
		);
		TextPrint(
			const std::string& name,
			bool visible,
			const std::filesystem::path &font, 
			const std::string& text,
			const Math::Vector2& pos,
			float rotation,
			float scale,
			Color color,
			float depth
		);

		RefFont Font = 0;
		Color Colour;
		std::string Text;

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void EditorInitialize() override;
		void EditorLoad() override;
		Reflection::UUID GetUUID() const noexcept override;
		void Draw2D() override;
		void EditorDraw2D(bool selected) override;
	};
}

REFL_FWD(TextPrint)