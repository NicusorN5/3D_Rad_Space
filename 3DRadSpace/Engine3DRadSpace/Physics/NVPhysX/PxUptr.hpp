#pragma once
#include "../../Core/Libs.hpp"

namespace Engine3DRadSpace::Physics::NVPhysX
{
	struct PxRelease
	{
		template<typename T>
		void operator()(T* ptr) const noexcept
		{
			if (ptr) ptr->release();
		}
	};

	template<typename T>
	using PxUPtr = std::unique_ptr<T, PxRelease>;
}