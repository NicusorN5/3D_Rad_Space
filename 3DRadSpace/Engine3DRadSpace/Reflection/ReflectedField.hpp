/// ------------------------------------------------------------------------------------------------
/// File:   Reflection/ReflectedField.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "FieldRepresentation.hpp"

namespace Engine3DRadSpace::Reflection
{
	class DLLEXPORT IReflectedField
	{
	protected:
		IReflectedField() = default;
		IReflectedField(const IReflectedField& f) = default;
		IReflectedField(IReflectedField&&) = default;

		IReflectedField& operator=(const IReflectedField& f) = default;
		IReflectedField& operator=(IReflectedField&& f) = default;
	public:
		virtual const size_t TypeHash() const noexcept = 0;
		virtual const std::string FieldName() const noexcept = 0;
		virtual const std::string FieldDesc() const noexcept = 0;
		virtual const size_t TypeSize() const noexcept = 0;
		virtual const ptrdiff_t FieldOffset() const noexcept = 0;

		virtual const void *Get(void *objPtr) const = 0;
		virtual void Set(void *objPtr,const void *value) const = 0;

		template<typename T>
		T GetAtOffset(void* objPtr, intptr_t offset)
		{
			return *std::launder<T>(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + FieldOffset() + offset));
		}

		virtual const void *DefaultValue() const = 0;

		virtual FieldRepresentation Representation() const = 0;

		virtual ~IReflectedField() = default;
	};

	template<ReflectableType T>
	class ReflectedField : public IReflectedField
	{
		const size_t _offset;
		const std::string _name;
		const std::string _desc;
		const T _defaultVal;
	public:
		ReflectedField(const size_t offset_obj_field,const std::string &visibleName,const std::string &description, T defaultValue) :
			_offset(offset_obj_field),
			_name(visibleName),
			_desc(description),
			_defaultVal(defaultValue)
		{
		}

		const size_t TypeHash() const noexcept override
		{
			return typeid(T).hash_code();
		}
		const std::string FieldName() const noexcept override
		{
			return _name;
		}
		const std::string FieldDesc() const noexcept override
		{
			return _desc;
		}
		const size_t TypeSize() const noexcept override
		{
			return sizeof(T);
		}
		const ptrdiff_t FieldOffset() const noexcept override
		{
			return _offset;
		}

		[[nodiscard]] const void *DefaultValue() const noexcept override
		{
			return reinterpret_cast<const void *>(&_defaultVal);
		}

		[[nodiscard]] const void *Get(void *objPtr) const override
		{
			assert(objPtr != nullptr);

			return std::launder(reinterpret_cast<T*>(static_cast<std::byte*>(objPtr) + _offset));
		}

		void Set(void *objPtr,const void *value) const override
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
		ReflectedField() = default;

		const size_t TypeHash() const noexcept override
		{
			return 0;
		}
		const std::string FieldName() const noexcept override
		{
			return std::string("");
		}
		const std::string FieldDesc() const noexcept override
		{
			return std::string("");
		}
		const size_t TypeSize() const noexcept override
		{
			return 0;
		}
		const ptrdiff_t FieldOffset() const noexcept override
		{
			return 0;
		}
		const void *Get(void *objPtr) const override
		{
			return nullptr;
		}
		void Set(void *objPtr,const void *value) const override
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