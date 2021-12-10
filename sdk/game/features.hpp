#pragma once
#include "../../common.hpp"

static enum DIRECTIONS
{
	NONE = 0,
	LEFT = 1,
	RIGHT = 2,
};

int direction = 0;

class features_t
{
private:
	void desync()
	{

	}

	void interactive_debug_camera()
	{

	}

	void fov_changer(float fov)
	{
		uintptr_t fov_cvar = memory.read_chain<uintptr_t>(globals.game_assembly, { o::Graphics_c, 0xb8 });
		memory.write<float>(fov_cvar + o::Graphics_fov, fov);
	}
public:
	void run()
	{
		while (true)
		{
			// shoot in air
			players.local->modelState()->setFlag(ModelState::Flags::OnGround);
			players.local->playerWalkMovement()->setGrounded(1.f);

			// spiderman
			players.local->playerWalkMovement()->setGroundAngle(0.f);
			players.local->playerWalkMovement()->setGroundAngleNew(0.f);

			// infinite jump
			players.local->playerWalkMovement()->setGroundTime(99999.f);
			players.local->playerWalkMovement()->setJumpTime(0.51f);
			players.local->playerWalkMovement()->setLandTime(0.3f);

			desync();
			interactive_debug_camera();
			fov_changer(120.f);

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
} features;