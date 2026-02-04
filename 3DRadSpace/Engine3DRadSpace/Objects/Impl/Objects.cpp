#include "Objects.hpp"
#include "../Reflection/Reflection.hpp"

//Forward declarations of object reflection data
REFL_FWD(Camera)
REFL_FWD(Sprite)
REFL_FWD(Skinmesh)
REFL_FWD(GForce)
REFL_FWD(Empty)
REFL_FWD(SkyColor)
REFL_FWD(TextPrint)
REFL_FWD(Fog)
REFL_FWD(Counter)
REFL_FWD(ExitFade)
REFL_FWD(Skybox)
REFL_FWD(SoundEffect)
REFL_FWD(SoundSource)

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

std::vector<ReflectedObject*> e3drsp_internal_objects_list;
bool e3drsp_internal_objects_list_initialized = false;

void Engine3DRadSpace::Internal::LoadDefaultObjects()
{
	if (e3drsp_internal_objects_list_initialized) return;

	e3drsp_internal_objects_list_initialized = true;

	auto ppDefaultObjects =
	{
		&CameraReflInstance, //Camera
		&CounterReflInstance, //Counter
		&EmptyReflInstance, //Empty
		/*
		CameraReflInstance, //Event On Key
		CameraReflInstance, //EventOnLocation
		*/
		&ExitFadeReflInstance, //ExitFade
		&FogReflInstance, //Fog
		/*
		CameraReflInstance, //Force
		CameraReflInstance, //FPVCamera
		CameraReflInstance, //Settings*/
		&GForceReflInstance, //G-Force
		/*
		CameraReflInstance, //Group
		CameraReflInstance, //Network chat
		CameraReflInstance, //Rigidbody
		CameraReflInstance, //C# Script
		*/
		&SkinmeshReflInstance, //Skinmesh
		&SkyboxReflInstance, //Skybox
		&SkyColorReflInstance,
		&SoundEffectReflInstance,
		&SoundSourceReflInstance,
		/*
		CameraReflInstance, //C++ source
		*/
		&SpriteReflInstance, //Sprite
		&TextPrintReflInstance, //Textprint
	};

	e3drsp_internal_objects_list.append_range(ppDefaultObjects);
}

ReflectedObject* Engine3DRadSpace::Internal::GetReflDataFromUUID(const Reflection::UUID& uuid)
{
	for(auto &refl : e3drsp_internal_objects_list)
	{
		if(uuid == refl->ObjectUUID)
			return refl;
	}
	return nullptr;
}
