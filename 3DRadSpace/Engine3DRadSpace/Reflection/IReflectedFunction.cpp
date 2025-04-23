#include "IReflectedFunction.hpp"

using namespace Engine3DRadSpace::Reflection;

IReflectedFunction::IReflectedFunction(
	unsigned int numParams,
	std::initializer_list<FieldRepresentation> fieldInfo,
	const FieldRepresentation& returnRepr,
	const std::string& name, 
	const std::string& signature,
	const std::type_info& info
) :
	IReflectedField(0,0, name, signature, info),
	_numArgs(numParams),
	_returnType(returnRepr),
	_argsInfo(fieldInfo.begin(), fieldInfo.end()),
	_name(name),
	_signature(signature)
{
}

unsigned int IReflectedFunction::NumParameters() const noexcept
{
	return _numArgs;
}

const std::vector<FieldRepresentation>& IReflectedFunction::ParametersInfo() const noexcept
{
	return _argsInfo;
}

const FieldRepresentation& IReflectedFunction::ReturnedTypeInfo() const noexcept
{
	return _returnType;
}

const std::string& IReflectedFunction::Name() const noexcept
{
	return _name;
}

const std::string& IReflectedFunction::Signature() const noexcept
{
	return _signature;
}

const void* IReflectedFunction::Get(void* objPtr) const
{
	return nullptr;
}

void IReflectedFunction::Set(void* objPtr, const void* value) const
{
}

const void* IReflectedFunction::DefaultValue() const
{
	return nullptr;
}

FieldRepresentation IReflectedFunction::Representation() const
{
	return FieldRepresentation();
}
