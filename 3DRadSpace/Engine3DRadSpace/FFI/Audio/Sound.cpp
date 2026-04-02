#include "Sound.h"
#include "../../Audio/sound.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Reflection;

E3DRSP_Sound E3DRSP_Sound_Create(E3DRSP_IAudioEngine audio, const char* path)
{
	if(audio == nullptr) return nullptr;
	if(path == nullptr) return nullptr;
	return new Sound(static_cast<AudioEngine*>(audio), path);
}

void E3DRSP_Sound_Destroy(E3DRSP_Sound audio)
{
	assert(audio != nullptr);
	delete static_cast<Sound*>(audio);
}