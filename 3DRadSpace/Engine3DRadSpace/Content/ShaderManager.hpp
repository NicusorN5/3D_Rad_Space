#pragma once
#include "../Graphics/Effect.hpp"
#include "../Core/Tag.hpp"

namespace Engine3DRadSpace::Content
{
	/// <summary>
	/// A type S is a ShaderCollection if it inherits Effect and is constructable from a GraphicsDevice pointer.
	/// </summary>
	template<typename S>
	concept ShaderCollection = std::is_base_of<Graphics::Shaders::Effect,S>::value
		&& requires(Graphics::GraphicsDevice* device)
	{
		S(device); //Shaders must be constructible from the graphics device.
	};

	/// <summary>
	/// A RTTI type-id <-> Effect dictionary.
	/// </summary>
	/// <remarks>
	/// Constructors are deleted since this is almost a namespace.
	/// </remarks>
	class E3DRSP_CONTENT_EXPORT ShaderManager
	{
		static std::unordered_map<size_t, std::shared_ptr<Graphics::Shaders::Effect>> _shaders;
	public:
		ShaderManager() = delete;
		ShaderManager(const ShaderManager &) = delete;
		ShaderManager(ShaderManager &&) noexcept = delete;

		ShaderManager &operator=(const ShaderManager &) = delete;
		ShaderManager &operator=(ShaderManager &&) noexcept = delete;

		/// <summary>
		/// Creates a shader of type S, then it is inserted into the internal dictionary(unordered map).
		/// </summary>
		/// <typeparam name="S">Shader effect type.</typeparam>
		/// <param name="device">Graphics device handle used to instantiate the shader.</param>
		/// <returns></returns>
		template<ShaderCollection S>
		static std::shared_ptr<S> LoadShader(Graphics::GraphicsDevice *device);

		/// <summary>
		/// Retrieves a shader instance of type S.
		/// </summary>
		/// <typeparam name="S">Effect type.</typeparam>
		/// <param name="t">Dummy variable. Use {} as a parameter.</param>
		/// <returns>An effect of type S.</returns>
		template<ShaderCollection S>
		static S* GetShader(Tag<S> t);

		/// <summary>
		/// Frees up the stored shaders.
		/// </summary>
		/// <remarks>
		/// Ideally, this should be called before the application exits.
		/// </remarks>
		static void ReleaseAll();
	};










	template<ShaderCollection S>
	inline std::shared_ptr<S> ShaderManager::LoadShader(Graphics::GraphicsDevice *device)
	{
		auto f = _shaders.find(typeid(S).hash_code());

		if(f == _shaders.end())
		{
			std::shared_ptr<S> ptr;
			ptr.reset(new S(device));

			_shaders.insert({typeid(S).hash_code(), ptr});
			return ptr;
		}
		else return std::static_pointer_cast<S>(f->second);
	}

	template<ShaderCollection S>
	inline S *ShaderManager::GetShader(Tag<S> t)
	{
		return static_cast<S*>(_shaders[typeid(S).hash_code()].get());
	}
}