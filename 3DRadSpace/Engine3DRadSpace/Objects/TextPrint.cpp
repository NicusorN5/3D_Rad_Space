#include "TextPrint.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Reflection;

TextPrint::TextPrint() :
    IObject2D("TextPrint", false, true, Vector2::Zero(), Vector2::One())
{
}

TextPrint::TextPrint(const std::string& name, bool visible, RefFont font, const std::string &text , const Math::Vector2& pos, float rotation, float scale, Color color, float depth) :
    IObject2D(name, false, visible, pos, Vector2(scale), rotation, Vector2::Zero(), depth ),
    Font(font),
    Colour(color)
{
}

TextPrint::TextPrint(const std::string& name, bool visible, const std::filesystem::path& font, const std::string& text, const Math::Vector2& pos, float rotation, float scale, Color color, float depth) :
    TextPrint(name, visible, 0, text, pos, rotation, scale, color, depth)
{
    _path = std::make_unique<std::string>(font.string());
}

void TextPrint::Initialize()
{
}

void TextPrint::Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt)
{
}

void TextPrint::Load(Content::ContentManager* content)
{
    if (_path != nullptr)
    {
        _font = content->Load<Graphics::Font>(*_path, &Font);
        _path.reset();
    }
    if (Font)
    {
        _font = static_cast<Graphics::Font*>((*content)[Font]);
    }
}

void TextPrint::Load(Content::ContentManager* content, const std::filesystem::path& path)
{
    _font = content->Load<Graphics::Font>(path, &Font);
}

void TextPrint::EditorInitialize()
{
}

void TextPrint::EditorLoad(Content::ContentManager* content)
{
    Load(content);
}

Reflection::UUID TextPrint::GetUUID() const noexcept
{
    // {12B25ECE-A980-4A58-9388-872AEA9FD2B5}
    return { 0x12b25ece, 0xa980, 0x4a58, { 0x93, 0x88, 0x87, 0x2a, 0xea, 0x9f, 0xd2, 0xb5 } };
}

void TextPrint::Draw(Graphics::SpriteBatch* spriteBatch, double dt)
{
    if (Visible)
    {
        spriteBatch->DrawString(_font, Text, Position, Scale.X, Colour, Rotation, FlipMode::None);
    }
}

void TextPrint::EditorDraw(Graphics::SpriteBatch* spriteBatch, double dt, bool selected)
{
    Draw(spriteBatch, dt);
}

REFL_BEGIN(TextPrint, "TextPrint", "2D Objects", "Text element on the screen")
REFL_FIELD(TextPrint, std::string, Name, "Name", "TextPrint", "Object name")
REFL_FIELD(TextPrint, bool, Visible, "Visible", true, "Is the text visible?")
REFL_FIELD(TextPrint, std::string, Text, "Text", "Hello world!", "Printed text")
REFL_FIELD(TextPrint, RefFont, Font, "Font", 0, "Font asset")
REFL_FIELD(TextPrint, Vector2, Position, "Position", Vector2::Zero(), "Normalized screen position X, Y in [0-1]")
REFL_FIELD(TextPrint, float, Rotation, "Rotation (rad)", 0.0f, "Rotations in radians")
REFL_FIELD(TextPrint, Vector2, Scale, "Scale", Vector2::One(), "Text scale, Y coordinate is ignored.")
REFL_FIELD(TextPrint, Color, Colour, "Color", Colors::White, "Text color")
REFL_FIELD(TextPrint, float, Depth, "Depth", 0.0f, "2D Depth")
REFL_END