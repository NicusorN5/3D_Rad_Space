#pragma once
#include "IReflectedField.hpp"

namespace Engine3DRadSpace::Reflection
{
	class E3DRSP_REFLECTION_EXPORT UnknownVariable final : public IReflectedField
	{
	public:
		UnknownVariable(
			size_t offset,
			size_t size,
			const std::string& name,
			const std::string& desc
		);

		const void* Get(void* objPtr) override;
		void Set(void* objPtr, const void* value) override;

		const void* DefaultValue() const override;

		FieldRepresentation Representation() const override;

		~UnknownVariable() override = default;
	};
}