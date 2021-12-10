#pragma once
#include "../../common.hpp"

class PlayerWalkMovement
{
public:
	void setCapsuleCenter(float center)
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::PlayerWalkMovement_capsuleCenter, center);
	}

	void setTargetMovement(Vector3 target)
	{
		memory.write<Vector3>(reinterpret_cast<uintptr_t>(this) + o::PlayerWalkMovement_targetMovement, target);
	}

	void setGrounded(float grounded)
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::PlayerWalkMovement_grounded, grounded);
	}

	void setSprinting(float sprinting)
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::PlayerWalkMovement_sprinting, sprinting);
	}

	void setGroundAngle(float angle)
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::PlayerWalkMovement_groundAngle, angle);
	}
	void setGroundAngleNew(float angle)
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::PlayerWalkMovement_groundAngleNew, angle);
	}

	void setJumpTime(float jump_time)
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::PlayerWalkMovement_jumpTime, jump_time);
	}

	void setGroundTime(float ground_time)
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::PlayerWalkMovement_groundTime, ground_time);
	}

	void setLandTime(float land_time)
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::PlayerWalkMovement_landTime, land_time);
	}
};