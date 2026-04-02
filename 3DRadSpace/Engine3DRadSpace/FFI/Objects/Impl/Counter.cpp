#include "Counter.h"
#include "../../../Objects/Impl/Counter.hpp"

using namespace Engine3DRadSpace::Objects;

E3DRSP_Counter E3DRSP_Counter_Create()
{
	return new Counter();
}

double E3DRSP_Camera_GetValue(E3DRSP_Counter counter)
{
	return static_cast<Counter*>(counter)->Value;
}

void E3DRSP_Camera_SetValue(E3DRSP_Counter counter, double value)
{
	static_cast<Counter*>(counter)->Value = value;
}

double E3DRSP_Camera_GetIncrement(E3DRSP_Counter counter)
{
	return static_cast<Counter*>(counter)->Increment;
}

void E3DRSP_Camera_SetIncrement(E3DRSP_Counter counter, double value)
{
	static_cast<Counter*>(counter)->Increment = value;
}

bool E3DRSP_Camera_IsLoadingFromFile(E3DRSP_Counter counter)
{
	return static_cast<Counter*>(counter)->LoadFromFile;
}

void E3DRSP_Camera_SetLoadingFromFile(E3DRSP_Counter counter, bool value)
{
	static_cast<Counter*>(counter)->LoadFromFile = value;
}

const char* E3DRSP_Camera_GetFile(E3DRSP_Counter counter)
{
	return static_cast<Counter*>(counter)->FilePath.c_str();
}

void E3DRSP_Camera_SetFile(E3DRSP_Counter counter, const char* path)
{
	static_cast<Counter*>(counter)->FilePath = path;
}

void E3DRSP_Camera_Save(E3DRSP_Counter counter)
{
	static_cast<Counter*>(counter)->Save();
}