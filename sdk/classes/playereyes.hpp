#pragma once
#include "../../common.hpp"

class PlayerEyes
{
public:
	void setViewOffset(Vector3 view_offset)
	{
		memory.write<Vector3>(reinterpret_cast<uintptr_t>(this) + o::PlayerEyes_viewOffset, view_offset);
	}

	Vector3 getViewOffset()
	{
		return memory.read<Vector3>(reinterpret_cast<uintptr_t>(this) + o::PlayerEyes_viewOffset);
	}

	void lookAtPoint(Vector2 angles)
	{
		angles.normalize();
		memory.write<Vector4>(reinterpret_cast<uintptr_t>(this) + o::PlayerEyes_bodyRotation, to_quat({ angles.x, angles.y, 0.f }));
	}
};