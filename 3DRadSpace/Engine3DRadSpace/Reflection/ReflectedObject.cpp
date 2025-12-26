#include "ReflectedObject.hpp"
#include "ReflectedObject.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;

ReflectedObject::ReflectedObject(
	const std::string& name,
	const std::string& category,
	const std::string& desc,
	const std::span<IReflectedField*> obj_fields,
	const UUID& uuid
) :
	Name(name),
	_fields(obj_fields.begin(), obj_fields.end()),
	Category(category),
	Description(desc),
	ObjectUUID(uuid)
{
	CreateBlankObject = []()
	{
		return nullptr;
	};
}

size_t ReflectedObject::NumFields() const noexcept
{
    return _fields.size()  - 1;
}

const IReflectedField* ReflectedObject::operator[](unsigned i)
{
    return _fields[i];
}

const IReflectedField* ReflectedObject::operator[](const std::string& name)
{
	//First find attempt: check if field name and name exactly match. O(#fields)
	for (auto& field : _fields)
	{
		if (field->FieldName() == name) return field;
	}

	return nullptr;
}

std::vector<IReflectedField *>::iterator ReflectedObject::begin()
{
	return _fields.begin();
}

std::vector<IReflectedField *>::iterator ReflectedObject::end()
{
	return std::prev(_fields.end()); //do not return the last element, it is a ReflectedField<void>.
}

ReflectedObject::~ReflectedObject()
{
	for (auto& field : *this)
	{
		delete field;
	}
}

E3DRSP_ReflectedObject E3DRSP_ReflectedObject_Create(
	const char* name,
	const char* category,
	const char* description,
	const E3DRSP_IReflectedField* fields,
	size_t numFields,
	const E3DRSP_UUID* objectUUID
)
{
	std::vector<IReflectedField*> natFields;
	for (size_t i = 0; i < numFields; ++i)
	{
		natFields.push_back(reinterpret_cast<IReflectedField*>(fields[i]));
	}

	return static_cast<E3DRSP_ReflectedObject>(new ReflectedObject(
		std::string(name),
		std::string(category),
		std::string(description),
		natFields,
		*std::bit_cast<const Reflection::UUID*>(objectUUID)
	));
}

const char* E3DRSP_ReflectedObject_GetName(E3DRSP_ReflectedObject obj)
{
	return reinterpret_cast<ReflectedObject*>(obj)->Name.c_str();
}

const char* E3DRSP_ReflectedObject_GetCategory(E3DRSP_ReflectedObject obj)
{
	return reinterpret_cast<ReflectedObject*>(obj)->Category.c_str();
}

const char* E3DRSP_ReflectedObject_GetDescription(E3DRSP_ReflectedObject obj)
{
	return reinterpret_cast<ReflectedObject*>(obj)->Description.c_str();
}

E3DRSP_UUID E3DRSP_ReflectedObject_GetUUID(E3DRSP_ReflectedObject obj)
{
	return std::bit_cast<E3DRSP_UUID>(reinterpret_cast<ReflectedObject*>(obj)->ObjectUUID);
}

size_t E3DRSP_ReflectedObject_GetNumFields(E3DRSP_ReflectedObject obj)
{
	return reinterpret_cast<ReflectedObject*>(obj)->NumFields();
}

const E3DRSP_IReflectedField E3DRSP_ReflectedObject_GetFieldByIndex(E3DRSP_ReflectedObject obj, size_t index)
{
	auto f = reinterpret_cast<ReflectedObject*>(obj)->operator[](static_cast<unsigned>(index));
	return reinterpret_cast<E3DRSP_IReflectedField>(const_cast<IReflectedField*>(f));
}

const E3DRSP_IReflectedField E3DRSP_ReflectedObject_GetFieldByName(E3DRSP_ReflectedObject obj, const char* name)
{
	auto f = reinterpret_cast<ReflectedObject*>(obj)->operator[](std::string(name));
	return reinterpret_cast<E3DRSP_IReflectedField>(const_cast<IReflectedField*>(f));
}

void* E3DRSP_ReflectedObject_CreateBlankObject(E3DRSP_ReflectedObject obj)
{
	return reinterpret_cast<ReflectedObject*>(obj)->CreateBlankObject();
}

void E3DRSP_ReflectedObject_Destroy(E3DRSP_ReflectedObject obj)
{
	delete reinterpret_cast<ReflectedObject*>(obj);
}