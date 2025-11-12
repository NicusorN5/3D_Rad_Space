#pragma once
#include "ITexture2D.hpp"
#include "IVertexBuffer.hpp"
#include "IIndexBuffer.hpp"
#include "IDepthStencilState.hpp"
#include "IRasterizerState.hpp"
#include "IBlendState.hpp"
#include "FlipMode.hpp"
#include "Font.hpp"
#include "Effect.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents how the sprite batch sorts the submitted sprites.
	/// </summary>
	enum class SpriteBatchSortMode
	{
		/// <summary>
		/// Do not sort the sprites.
		/// </summary>
		Immediate,
		/// <summary>
		/// Sort by texture. Use this if you want to optimize the number of draw calls.
		/// </summary>
		SortedByTexture,
		/// <summary>
		/// Sort by depth. From front (0.0f) to back (-inf).
		/// </summary>
		SortedByDepth_FrontToBack,
		/// <summary>
		/// Sort by depth. From back (-inf) to front (0.0f).
		/// </summary>
		SortedByDepth_BackToFront,
	};

	/// <summary>
	/// A SpriteBatch renders 2D sprites with a specified order.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT SpriteBatch
	{
		IGraphicsDevice *_device;
		SpriteBatchSortMode _sortingMode;
		enum SpriteBatchState
		{
			Immediate,
			BeginCalled,
			EndCalled
		} _state;

		std::unique_ptr<Effect> _spriteShader;

		std::unique_ptr<IVertexBuffer> _vertexBuffer;
		std::unique_ptr<IIndexBuffer> _indexBuffer;
		size_t _capacity = 256;

		struct spriteBatchEntry
		{
			unsigned textureID;
			std::pair<Math::Vector2,Math::Vector2> coords;
			Math::RectangleF uvSource;
			Math::Color tintColor;
			bool flipU;
			bool flipV;
			float rotation;
			float depth;
			SpriteBatchSortMode sortingMode;

			bool operator >(const spriteBatchEntry &b) const;
			bool operator <(const spriteBatchEntry &b) const;
			bool operator ==(const spriteBatchEntry &b) const;
		};

		std::multiset<spriteBatchEntry> _entries;

		std::vector<ITexture2D*> _textures;

		static std::array<VertexPointUVColor, 4> _createQuad(
			const Math::RectangleF &r,
			bool flipU = false,
			bool flipV = false,
			const Math::Color &tintColor = Math::Colors::White,
			const Math::RectangleF &uvRect = Math::RectangleF(0.0f,0.0f,1.0f,1.0f)
		);
		
		static std::array<VertexPointUVColor, 4> _createQuad(
			const Math::Vector2& a,
			const Math::Vector2& b,
			const Math::Vector2& c,
			const Math::Vector2& d,
			bool flipU,
			bool flipV,
			const Math::Color &tintColor = Math::Colors::White, 
			const Math::RectangleF &uvRect = Math::RectangleF(0.0f,0.0f,1.0f,1.0f)
		);
		
		static std::array<unsigned, 6> _createIndexQuad(unsigned offset);
		
		void _prepareGraphicsDevice();

		void _drawEntry(const spriteBatchEntry& entry);
		void _drawAllEntries_SortByTexture();
		void _drawAllEntries();
		void _restoreGraphicsDevice();

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _oldRasterizerState;

		Microsoft::WRL::ComPtr<ID3D11BlendState> _oldBlendState;
		float _oldBlendFactor[4];
		unsigned _oldSampleMask;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _oldStencilState;
		unsigned _oldStencilRef;

		std::unique_ptr<IRasterizerState> _rasterizerState;
		std::unique_ptr<ISamplerState> _samplerState;
		std::unique_ptr<IDepthStencilState> _depthBufferState;
		std::unique_ptr<IBlendState> _blendState;
	public:
		/// <summary>
		/// Constructs a sprite batch.
		/// </summary>
		/// <param name="device">Graphics device</param>
		SpriteBatch(IGraphicsDevice *device);

		SpriteBatch(SpriteBatch &) = delete;
		SpriteBatch(SpriteBatch &&) noexcept = default;

		SpriteBatch& operator=(SpriteBatch &) = delete;
		SpriteBatch& operator=(SpriteBatch &&) noexcept = default;

		void Begin(SpriteBatchSortMode sortingMode = SpriteBatchSortMode::Immediate);
		void Begin(SpriteBatchSortMode sortingMode, std::unique_ptr<ISamplerState> &&samplerState);
		
		void DrawNormalized(
			ITexture2D* texture,
			const Math::RectangleF& coords,
			const Math::RectangleF& source = Math::RectangleF(0.0f, 0.0f, 1.0f, 1.0f),
			Math::Color tintColor = Math::Colors::White,
			float rotation = 0.0f, 
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		void DrawNormalized(
			ITexture2D* texture,
			const Math::RectangleF& coords,
			const Math::Rectangle source,
			Math::Color tintColor = Math::Colors::White,
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		void Draw(
			ITexture2D* texture,
			const Math::Rectangle& coords,
			const Math::Rectangle& source,
			Math::Color tintColor = Math::Colors::White,
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);
		void Draw(
			ITexture2D* texture, 
			const Math::Rectangle& coords,
			Math::Color tintColor = Math::Colors::White,
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		void DrawString(
			Font* font,
			const std::string& text, 
			const Math::Vector2& pos,
			float size,
			Math::Color tintColor = Math::Colors::White,
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		void DrawString(
			Font* font, 
			const std::string& text,
			const Math::Point& pos, 
			float size, 
			Math::Color tintColor = Math::Colors::White, 
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		void End();

		~SpriteBatch() = default;
	};
}