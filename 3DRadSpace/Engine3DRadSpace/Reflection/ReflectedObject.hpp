#pragma once
#include "ReflectedField.hpp"
#include "UUID.hpp"
#include "../Core/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<typename O>
	concept ReflectableObject = std::is_default_constructible_v<O>;

	template<ReflectableObject O>
	struct ObjectTag {};

	class E3DRSP_REFLECTION_EXPORT ReflectedObject
	{
		std::vector<IReflectedField*> _fields;

		template<ReflectableObject O>
		UUID determineUUID(ObjectTag<O> tag)
		{
			Internal::AssetUUIDReader r;
			return r.GetUUID<O>();
		}
	public:
		template<ReflectableObject O>
		ReflectedObject(ObjectTag<O> tag, const std::string &name, const std::string &category, const std::string &desc, std::initializer_list<IReflectedField *> obj_fields) :
			Name(name),
			_fields(obj_fields),
			Category(category),
			Description(desc),
			ObjectUUID(determineUUID<O>(tag))
		{
			CreateBlankObject = []()
			{
				return new O();
			};
		}

		std::string Name;
		std::string Category;
		std::string Description;
		UUID ObjectUUID;

		size_t NumFields() const noexcept;
		const IReflectedField *operator[](unsigned i);
		const IReflectedField *operator[](const std::string &name);

		std::vector<IReflectedField *>::iterator begin();
		std::vector<IReflectedField *>::iterator end();

		std::function<IObject *()> CreateBlankObject;

		~ReflectedObject();
	};
}