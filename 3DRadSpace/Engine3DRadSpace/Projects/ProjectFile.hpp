#pragma once
#include "../ObjectList.hpp"

namespace Engine3DRadSpace::Projects
{
	ObjectList Load(std::filesystem::path& path);
	void Save(const ObjectList& list, std::filesystem::path& path);
}