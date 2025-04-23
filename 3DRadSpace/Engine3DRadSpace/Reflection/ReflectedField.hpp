#pragma once
#include "IReflectedField.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<ReflectableType T>
	class ReflectedField : public IReflectedField
	{
		T _defaultVal;
	public:
		ReflectedField(
			const size_t offset_obj_field,
			const std::string &visibleName,
			const std::string &description,
			T defaultValue
		) :
			IReflectedField(offset_obj_field, sizeof(T), visibleName, description, typeid(T)),
			_defaultVal(defaultValue)
		{
		}

		[[nodiscard]] const void* DefaultValue() const noexcept override
		{
			return static_cast<const void *>(&_defaultVal);
		}

		[[nodiscard]] const void* Get(void *objPtr) const override
		{
			assert(objPtr != nullptr);

			return std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset));
		}

		void Set(void *objPtr, const void *value) const override
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			T* lhs = std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset)); 
			const T* rhs = static_cast<const T*>(value);

			*lhs = *rhs;
		}

		template<typename T>
		void Set(void* objPtr, const T* value)  const
		{
			assert(objPtr != nullptr);
			assert(value != nullptr);

			T* lhs = std::launder<T>(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset));
			const T* rhs = static_cast<const T*>(value);
			
			*lhs = *rhs;
		}

		template<typename T>
		T Get(void* objPtr) const
		{
			assert(objPtr != nullptr);

			return T(*std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset)));
		}

		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<T>();
		}

		~ReflectedField() override = default;
	};

	/// Null specialization. Sentinel value.
	template<>
	class DLLEXPORT ReflectedField<void> final : public IReflectedField
	{
	public:
		ReflectedField() : IReflectedField(0, 0, "", "", typeid(void))
		{
		}

		const void *Get(void *objPtr) const override
		{
			return nullptr;
		}
		void Set(void *objPtr, const void *value) const override
		{
		}
		const void *DefaultValue() const noexcept override
		{
			return nullptr;
		}
		FieldRepresentation Representation() const noexcept override
		{
			return GetFieldRepresentation<void>();
		}
	};
}