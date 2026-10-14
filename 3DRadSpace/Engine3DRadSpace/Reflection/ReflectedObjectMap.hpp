#pragma once
#include "ReflectedObject.hpp"
#include "ReflectedField.hpp"
#include "IReflectedFunction.hpp"
#include "Attribute.hpp"
#include "../Math/Quaternion.hpp"

namespace Engine3DRadSpace::Reflection
{
	class FieldMap
	{
		template<typename T, typename Fn>
		static void iterate(const ReflectedObject* refl, const Objects::IObject* obj, Fn&& fn)
		{
			for (auto& field : *refl)
			{
				if (auto f = dynamic_cast<ReflectedField<Type>*>(field); f != nullptr)
				{
					fn.operator()<T>(field, obj));
				}
			}
		}

		template<typename T, typename Fn>
		static void iterate(const ReflectedObject* refl, Objects::IObject* obj, Fn&& fn)
		{
			for (auto& field : *refl)
			{
				if (field == nullptr) continue;
				if (dynamic_cast<IReflectedFunction*>(field) != nullptr)
					continue;
				if (dynamic_cast<Attribute*>(field) != nullptr)
					continue;
				if (auto f = dynamic_cast<ReflectedField<Type>*>(field))
				{
					fn.operator()<T>(field, obj));
				}
			}
		}
	public:
		template<typename T, typename Fn>
		static T Read(const ReflectedObject* refl, const Objects::IObject* obj, Fn&& fn)
		{
			if constexpr (std::is_same_v<T, void>)
			{
				iterate(refl, obj, std::forward<Fn>(fn));
				return;
			}
			else
			{
				std::vector<T> r;
				iterate(refl, obj, [](const ReflectedField* refl, const Objects::IObject* obj)
					{
						r.emplace_back(std::forward(fn).operator<T>(field, obj));
					}
				);
				return r;
			}
		}

		template<typename T, typename Fn>
		static T Write(const ReflectedObject* refl, Objects::IObject* obj, Fn&& fn)
		{
			if constexpr (std::is_same_v<T, void>)
			{
				iterate(refl, obj, std::forward<Fn>(fn));
				return;
			}
			else
			{
				std::vector<T> r;
				iterate(refl, obj, [](const ReflectedField* refl, const Objects::IObject* obj)
					{
						r.emplace_back(std::forward(fn).operator<T>(field, obj));
					}
				);
				return r;
			}
		}

		std::vector<IReflectedField*> AllFields(const ReflectedObject* refl)
		{
			std::vector<IReflectedField*> r;
			iterate(refl, nullptr, [&](const ReflectedField* field, const Objects::IObject* obj)
				{
					r.emplace_back(field);
				}
			);
			return r;
		}

		std::vector<IReflectedFunction*> AllFunctions(const ReflectedObject* refl)
		{
			std::vector<IReflectedFunction*> r;
			for (auto& field : *refl)
			{
				if (field == nullptr) continue;
				if (auto f = dynamic_cast<IReflectedFunction*>(field))
				{
					r.emplace_back(f);
				}
			}
			return r;
		}

		std::vector<IReflectedField*> AllAttributes(const ReflectedObject* refl)
		{
			std::vector<IReflectedField*> r;
			for (auto& field : *refl)
			{
				if (field == nullptr) continue;
				if (auto f = dynamic_cast<Attribute*>(field))
				{
					r.emplace_back(f);
				}
			}
			return r;
		}
	};
}