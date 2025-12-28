#pragma once
#include "Libs.hpp"
#include "IService.hpp"
#include "Tag.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Base interface for a game class.
	/// </summary>
	class E3DRSP_CORE_EXPORT IGame
	{
	protected:
		std::unordered_map<std::type_index, IService*> _services;
	public:
		template<typename T>
		void AddService(T* service)
		{
			_services[typeid(T)] = service;
		}

		IService* GetService(const std::type_index &type);

		template<typename T>
		T* GetService(Tag<T> dummy)
		{
			(void)dummy;
			return static_cast<T*>(GetService(typeid(T)));
		}

		virtual IService* RequireService(const std::type_index& type);

		template<typename T>
		T* RequireService(Tag<T> dummy)
		{
			return RequireService(typeid(T));
		}

		virtual void Exit() = 0;

		std::unordered_map<std::type_index, IService*>::iterator begin();
		std::unordered_map<std::type_index, IService*>::iterator end();

		virtual bool WasInitialized() const noexcept = 0;
		virtual bool WasLoaded() const noexcept = 0;

		virtual void AppendScene(const std::filesystem::path& path) = 0;

		virtual ~IGame() = default;
	};
}