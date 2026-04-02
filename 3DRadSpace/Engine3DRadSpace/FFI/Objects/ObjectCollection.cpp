#include "ObjectCollection.h"
#include "../../Objects/ObjectCollection.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

E3DRSP_ObjectCollection E3DRSP_ObjectCollection_Create()
{
	return new ObjectCollection();
}

void E3DRSP_ObjectCollection_Add(E3DRSP_ObjectCollection collection, E3DRSP_IObject object)
{
	static_cast<ObjectCollection*>(collection)->Add(static_cast<IObject*>(object));
}

void E3DRSP_ObjectCollection_Remove(E3DRSP_ObjectCollection collection, E3DRSP_IObject object)
{
	static_cast<ObjectCollection*>(collection)->Remove(static_cast<IObject*>(object));
}

void E3DRSP_ObjectCollection_RemoveID(E3DRSP_ObjectCollection collection, size_t index)
{
	static_cast<ObjectCollection*>(collection)->Remove(index);
}

E3DRSP_IObject E3DRSP_ObjectCollection_At(E3DRSP_ObjectCollection collection, size_t index)
{
	return static_cast<E3DRSP_IObject>(static_cast<ObjectCollection*>(collection)->operator[](index));
}

size_t E3DRSP_ObjectCollection_Count(E3DRSP_ObjectCollection collection)
{
	return static_cast<ObjectCollection*>(collection)->Count();
}

void E3DRSP_ObjectCollection_Clear(E3DRSP_ObjectCollection collection)
{
	static_cast<ObjectCollection*>(collection)->Clear();
}