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

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

std::vector<ReflectedObject*> _3drsp_internal_objects_list;

void Engine3DRadSpace::Internal::LoadDefaultObjects()
{
	if(_3drsp_internal_objects_list.size() != 0) return;

	_3drsp_internal_objects_list =
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
		/*
		CameraReflInstance, //Skybox
		*/
		&SkyColorReflInstance,
		/*
		CameraReflInstance, //SoundEffect
		CameraReflInstance, //SoundSource
		CameraReflInstance, //C++ source
		*/
		&SpriteReflInstance, //Sprite
		&TextPrintReflInstance, //Textprint
	};
}

ReflectedObject* Engine3DRadSpace::Internal::GetReflDataFromUUID(const Reflection::UUID& uuid)
{
	for(auto &refl : _3drsp_internal_objects_list)
	{
		if(uuid == refl->ObjectUUID)
			return refl;
	}
	return nullptr;
}
