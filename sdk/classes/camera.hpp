#pragma once
#include "../../common.hpp"

struct vmatrix_t
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

class camera_t
{
private:
	Vector3 position{};
	vmatrix_t vmatrix{};
public:
	bool set_position(Vector3 _position)
	{
		position = _position;
		return (bool)(position.x && position.y && position.z);
	}

	void set_vmatrix(vmatrix_t _vmatrix)
	{
		vmatrix = _vmatrix;
	}

	Vector3 get_position()
	{
		return position;
	}
	
	vmatrix_t get_vmatrix()
	{
		return vmatrix;
	}

	uintptr_t get_object()
	{
		/* gom -> tagged_object -> game_object -> object_class -> camera_instance */
		const uintptr_t object = memory.read_chain<uintptr_t>(globals.unity_player, { o::GameObjectManager, 0x08, 0x10, 0x30 });
		const uintptr_t camera = memory.read<uintptr_t>(object + 0x18);
		return camera;
	}
} camera;

bool world_to_screen(const Vector3& entity_position, Vector2& screen_position)
{
	Vector3 transform{ camera.get_vmatrix()._14, camera.get_vmatrix()._24, camera.get_vmatrix()._34};
	Vector3 right{ camera.get_vmatrix()._11, camera.get_vmatrix()._21, camera.get_vmatrix()._31 };
	Vector3 up{ camera.get_vmatrix()._12, camera.get_vmatrix()._22, camera.get_vmatrix()._32 };

	float w = transform.dot(entity_position) + camera.get_vmatrix()._44;

	Vector2 pos{ right.dot(entity_position) + camera.get_vmatrix()._41, up.dot(entity_position) + camera.get_vmatrix()._42 };

	if (w < 0.098f)
		return false;

	screen_position = Vector2(globals.screen_center_x * (1 + pos.x / w), globals.screen_center_y * (1 - pos.y / w));

	return true;
}