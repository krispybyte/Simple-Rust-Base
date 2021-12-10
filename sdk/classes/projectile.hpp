#pragma once
#include "../../common.hpp"

class Projectile
{
public:
	float getDrag()
	{
		return memory.read<float>(reinterpret_cast<uintptr_t>(this) + o::Projectile_drag);
	}

	float getGravityModifier()
	{
		return memory.read<float>(reinterpret_cast<uintptr_t>(this) + o::Projectile_gravityModifier);
	}
	
	float getThickness()
	{
		return memory.read<float>(reinterpret_cast<uintptr_t>(this) + o::Projectile_thickness);
	}
};