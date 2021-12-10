#include "../../common.hpp"

#include <math.h>

static enum TARGETS
{
	HEAD = 47,
	BODY = 21,
	NEAREST = 3,
};

int bone_target = TARGETS::HEAD;

class aimbot_t
{
private:
	Vector3 prediction(Vector3 position)
	{
		Item* item = players.local->getHeldItem();

		bullet_info info{};

		info = item->baseProjectile()->getBulletInfo();

		float distance_to = camera.get_position().distance(position);
		float bullet_speed = info.velocity * (info.velocity_scale * info.velocity_scalar);
		float bullet_gravity = info.gravity;
		float bullet_time = distance_to / bullet_speed;
		float bullet_drag = info.drag;

		Vector3 direction = position - camera.get_position();
		float target_distance = std::sqrt((direction.x) * (direction.x) + (direction.z) * (direction.z));
		float bullet_drop = calculate_bullet_drop(direction.y, target_distance, bullet_speed, bullet_gravity);

		const float time_step = 0.015625f;

		float travelled;
		float speed;
		float time;
		float divider;

		for (float distance_to_travel = 0.f; distance_to_travel < distance_to;)
		{
			float speed_modifier = 1.f - time_step * bullet_drag;
			bullet_speed *= speed_modifier;

			if (bullet_speed <= 0.f || bullet_speed >= 10000.f || travelled >= 10000.f || travelled < 0.f)
				break;

			if (time > 8.f)
				break;

			speed += (9.81f * bullet_gravity) * time_step;
			speed *= speed_modifier;

			distance_to_travel += bullet_speed * time_step;
			travelled += speed * time_step;
			time += time_step;
		}

		Vector3 new_target = position;

		Vector3 velocity = players.aimbot_target->playerModel()->getTargetVelocity() * 0.75f;

		if (velocity.y > 0.f)
			velocity.y /= 3.25f;

		new_target.y += bullet_drop;
		new_target += velocity * time;
		return new_target;
	}

	Vector3 find_target()
	{
		BasePlayer* temp_target{};

		Vector2 center = { globals.screen_center_x, globals.screen_center_y };

		float smallest_distance = FLT_MAX;
		Vector3 final_aimpoint{};

		for (const auto& entity : entity_list.player_list)
		{
			BasePlayer* player = memory.read<BasePlayer*>(entity + 0x28);

			if (!player)
				continue;

			if (player->isDead())
				continue;

			if (!player->playerModel()->isVisible())
				continue;

			Vector3 aimpoint{};

			if (bone_target != TARGETS::NEAREST) aimpoint = player->getBone((bone_list)bone_target);

			if (bone_target == TARGETS::NEAREST)
			{
				Vector3 head = player->getBone(bone_list::head);
				Vector2 head_screen{};

				if (!world_to_screen(head, head_screen))
					continue;

				Vector3 body = player->getBone(bone_list::head);
				Vector2 body_screen{};
			
				if (!world_to_screen(body, body_screen))
					continue;

				float body_distance = body_screen.distance(center);
				float head_distance = head_screen.distance(center);

				if (body_distance < head_distance)
					aimpoint = body;

				if (head_distance < body_distance)
					aimpoint = head;
			}
			
			Vector2 aimpoint_screen{};

			if (!world_to_screen(aimpoint, aimpoint_screen))
				continue;

			float current_distance = aimpoint_screen.distance(center);

			if (current_distance < smallest_distance)
			{
				temp_target = player;
				smallest_distance = current_distance;
				final_aimpoint = aimpoint;
			}
		}

		players.aimbot_target = temp_target;

		return final_aimpoint;
	}
public:
	void run()
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(5));

			if (!GetAsyncKeyState(VK_XBUTTON2))
				continue;

			Vector3 target = prediction(find_target());

			if (players.local->getHeldItem()->isValid())
			{
				/* regular */
				players.local->playerInput()->setViewAngles(calculate_angle(camera.get_position(), target));
				/* silent-aim */
				//players.local->eyes()->lookAtPoint(calculate_angle(camera.get_position(), target));
			}
		}
	}

}aimbot;