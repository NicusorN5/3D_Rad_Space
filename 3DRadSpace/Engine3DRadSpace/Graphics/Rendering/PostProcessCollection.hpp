#pragma once
#include "PostProcessEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class DLLEXPORT PostProcessCollection
	{
	private:
		GraphicsDevice* _device;
		std::vector<std::unique_ptr<PostProcessEffect>> _effects;
	public:
		PostProcessCollection(GraphicsDevice* device);

		PostProcessCollection(PostProcessCollection&&) noexcept = default;
		PostProcessCollection& operator=(PostProcessCollection&&) noexcept = default;

		template<typename E>
		E& Add(bool avoid_duplicate = true)
		{
			if(avoid_duplicate)
			{
				auto index = Exists<E>();
				if(index.has_value())
				{
					return *dynamic_cast<E*>(_effects[index.value()].get());
				}
			}

			_effects.push_back(std::make_unique<E>(_device));
			return *dynamic_cast<E*>(_effects[_effects.size() - 1].get());
		}

		template<typename E>
		E* At(int index)
		{
			return dynamic_cast<E*>(_effects[index].get());
		}

		template<typename E>
		std::optional<size_t> Exists()
		{
			for(size_t i = 0; i < _effects.size(); i++)
			{
				if(dynamic_cast<E*>(_effects[i].get()) != nullptr)
				{
					return i;
				}
			}
			return std::nullopt;
		}

		template<typename E>
		E& Get()
		{
			auto index = Exists<E>();
			if(index.has_value())
			{
				return *dynamic_cast<E*>(_effects[index.value()].get());
			}
			else
			{
				throw std::exception("Effect not found!");
			}
		}

		template<typename E>
		E* TryGet()
		{
			auto index = Exists<E>();
			if(index.has_value())
			{
				return dynamic_cast<E*>(_effects[index.value()].get());
			}
			else
			{
				return nullptr;
			}
		}

		/// <summary>
		/// Gets the Nth effect of type E.
		/// </summary>
		/// <typeparam name="E">Effect type</typeparam>
		/// <param name="index"></param>
		/// <returns></returns>
		template<typename E>
		E& GetNth(int index)
		{
			int count = 0;
			for(size_t i = 0; i < _effects.size(); i++)
			{
				if(dynamic_cast<E*>(_effects[i].get()) != nullptr)
				{
					if(count == index)
					{
						return *dynamic_cast<E*>(_effects[i].get());
					}
					count++;
				}
			}

			throw std::exception("Effect not found!");
		}

		size_t Length() const noexcept;

		void ApplyAll();
	};
}