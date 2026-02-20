#include "Counter.hpp"
#include "Counter.h"
#include <fstream>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

Counter::Counter() : Counter("Counter", 0, 1)
{
}

Counter::Counter(const std::string& name, double vaulue, double increment) :
	IObject(name, false),
	Value(vaulue),
	Increment(increment)
{
}

void Counter::Initialize()
{
}

void Counter::Load()
{
	if(this->LoadFromFile)
	{
		std::ifstream file(FilePath);
		if(file.is_open())
		{
			file >> Value;
			file.close();
		}
		else
		{
			Save();
		}
	}
}

void Counter::Save()
{
	std::ofstream create_file(FilePath);
	create_file << Value;
	create_file.close();
}

Reflection::UUID Counter::GetUUID() const noexcept
{
	// {915D5743-9333-4DCD-BEDA-908612AD87D6}
	return { 0x915d5743, 0x9333, 0x4dcd, { 0xbe, 0xda, 0x90, 0x86, 0x12, 0xad, 0x87, 0xd6 } };
}

void Counter::Load(const std::filesystem::path& path)
{
	FilePath = path.string();
}

void Counter::Update()
{
	if(Enabled)
	{
		Value += Increment;
		Enabled = false;
	}
}

Gizmos::IGizmo* Counter::GetGizmo() const noexcept
{
	return nullptr;
}

Counter::~Counter()
{
	Save();
}

REFL_BEGIN(Counter, "Counter", "Events", "Counter")
	REFL_FIELD(Counter, std::string, Name, "Name", "Counter", "Counter name")
	REFL_FIELD(Counter, double, Value, "Value", 0, "The value of the counter")
	REFL_FIELD(Counter, double, Increment, "Increment", 1, "The increment of the counter")
	REFL_FIELD(Counter, bool, LoadFromFile, "Use file?", false, "Load the counter value from a file?")
	REFL_FIELD(Counter, std::string, FilePath, "File path", "", "The path of the file to load the counter value from")
REFL_END

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