#pragma once
#include "../../common.hpp"

class ModelState
{
public:
	static enum Flags
	{
		Ducked = 1,
		Jumped = 2,
		OnGround = 4,
		Sleeping = 8,
		Sprinting = 16,
		OnLadder = 32,
		Flying = 64,
		Aiming = 128,
		Prone = 256,
		Mounted = 512,
		Relaxed = 1024,
		OnPhone = 2048,
		Crawling = 4096
	};

	void setWaterLevel(float level)
	{
		memory.write<float>(reinterpret_cast<uintptr_t>(this) + o::ModelState_waterLevel, level);
	}

	bool hasFlag(int flag)
	{
		return (memory.read<int>(reinterpret_cast<uintptr_t>(this) + o::ModelState_flags)) & flag;
	}

	void setFlag(int flag)
	{
		int current_flags = memory.read<int>(reinterpret_cast<uintptr_t>(this) + o::ModelState_flags);
		memory.write<int>(reinterpret_cast<uintptr_t>(this) + o::ModelState_flags, current_flags |= flag);
	}

	void unsetFlag(int flag)
	{
		uintptr_t player_flags = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + o::ModelState_flags);

		if (hasFlag(flag))
			player_flags -= flag;

		memory.write<uintptr_t>(reinterpret_cast<uintptr_t>(this) + o::ModelState_flags, player_flags);
	}
};