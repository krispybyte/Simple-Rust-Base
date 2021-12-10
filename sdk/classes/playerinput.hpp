#pragma once
#include "../../common.hpp"

class PlayerInput
{
public:
	Vector2 getViewAngles()
	{
		return memory.read<Vector2>(reinterpret_cast<uintptr_t>(this) + o::PlayerInput_bodyAngles);
	}

	void setViewAngles(Vector2 angles)
	{
		memory.write<Vector2>(reinterpret_cast<uintptr_t>(this) + o::PlayerInput_bodyAngles, angles);
	}

	Vector4 getRotation()
	{
		return memory.read<Vector4>(reinterpret_cast<uintptr_t>(this) + o::PlayerInput_bodyRotation);
	}
};


