#pragma once
#include "IReflectedField.hpp"

namespace Engine3DRadSpace::Reflection
{
	class DLLEXPORT IReflectedFunction : public IReflectedField
	{
	protected:
		IReflectedFunction(
			unsigned int numParams,
			std::initializer_list<FieldRepresentation> fieldInfo,
			const FieldRepresentation &returnRepr,
			const std::string& name,
			const std::string& signature,
			const std::type_info& info
		);
	
		unsigned int _numArgs;
		FieldRepresentation _returnType;
		std::vector<FieldRepresentation> _argsInfo;
		std::string _name;
		std::string _signature;

		IReflectedFunction(const IReflectedFunction&) = default;
		IReflectedFunction(IReflectedFunction&&) noexcept = default;

		IReflectedFunction& operator=(const IReflectedFunction&) = default;
		IReflectedFunction& operator=(IReflectedFunction&&) noexcept = default;

	public:
		unsigned int NumParameters() const noexcept;
		const std::vector<FieldRepresentation>& ParametersInfo() const noexcept;
		const FieldRepresentation& ReturnedTypeInfo() const noexcept ;
		const std::string& Name() const noexcept;
		const std::string& Signature() const noexcept;

		virtual std::any Invoke(void* self, std::span<std::any> args) const = 0;
		virtual void Invoke(void* outReturn, void* self, std::span<void*> args) const = 0;

		virtual ~IReflectedFunction() = default;

		// Inherited via IReflectedField
		const void* Get(void* objPtr) const override;
		void Set(void* objPtr, const void* value) const override;
		const void* DefaultValue() const override;
		FieldRepresentation Representation() const override;
	};
}