#pragma once
#include "../../common.hpp"

class prefab_t
{
public:
	uintptr_t transform;
	Vector3 position;
	std::string name;
public:
	prefab_t(uintptr_t entity_address, uintptr_t entity_transform, uintptr_t game_object)
	{
		this->transform = memory.read<uintptr_t>(entity_transform + 0x38);
		this->position = memory.read<Vector3>(this->transform + 0x90);
		this->name = memory.read_str(memory.read<uintptr_t>(game_object + 0x60), 1024);

		/* for dropped items */
		if (this->name.find(_("item_drop.prefab")) != std::string::npos)
			this->name = _("item drop");

		/* removes (world)*/
		std::string world_str = _(" (world)");
		if (this->name.find(world_str) != std::string::npos)
			this->name.erase(this->name.find(world_str), world_str.length());

		/* changes dots to spaces between names */
		std::replace(this->name.begin(), this->name.end(), '.', ' '); // replace all dots in name with a space, looks nicer
	}

	prefab_t() = default;

	~prefab_t()
	{
		this->transform = NULL;
		this->position = { 0.f, 0.f, 0.f };
		this->name = _("");
	}

	std::string get_name()
	{
		return this->name;
	}

	void update()
	{
		if (!this->position.is_valid())
			this->position = memory.read<Vector3>(this->transform + 0x90);
	}
};
