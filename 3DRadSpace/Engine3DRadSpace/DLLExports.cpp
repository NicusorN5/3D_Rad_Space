#include "3DRadSpace.hpp"

using namespace Engine3DRadSpace;

extern "C"
{
	DLLEXPORT void* create_Window(const char*title, unsigned x, unsigned y)
	{
		return new Window(title, x, y);
	}

	DLLEXPORT void destruct_Window(void* window)
	{
		delete static_cast<Window*>(window);
	}
}