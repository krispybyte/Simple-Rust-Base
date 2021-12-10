#pragma once
#include "../../common.hpp"
#include <string>

typedef unsigned int list_size;

#define PLAYER_TAG 6

struct list_info_t
{
	std::vector<uintptr_t> address{};
	int size = NULL;
	uintptr_t list = NULL;
	uintptr_t base = NULL;
};

class entity_list_t
{
private:
	list_info_t get_list()
	{
		list_info_t list_info{};
		
		list_info.list = memory.read_chain<uintptr_t>(globals.base_networkable, { 0xb8, 0x00, 0x10, 0x28 });
		list_info.base = memory.read<uintptr_t>(list_info.list + 0x18);
		list_info.size = memory.read<int>(list_info.list + 0x10);
		
		/* create our buffer */
		std::unique_ptr<uintptr_t> entities_buffer(new uintptr_t[list_info.size * sizeof(uintptr_t)]);

		/* read into the buffer */
		memory.read(list_info.base + 0x20, entities_buffer.get(), list_info.size * sizeof(uintptr_t));
		
		/* set address in struct */
		list_info.address = { entities_buffer.get(), entities_buffer.get() + (uintptr_t)list_info.size};
		
		return list_info;
	}
public:
	std::vector<uintptr_t> object_list{};

	std::vector<uintptr_t> player_list{};
	std::vector<prefab_t> prefab_list{};

	void cache()
	{
		std::vector<uintptr_t> temp_player_list{};
		std::vector<prefab_t> temp_prefab_list{};

		object_list = get_list().address;

		for (const auto& object : object_list)
		{
			uintptr_t gameobject = memory.read_chain<uintptr_t>(object, { 0x10, 0x30 });
			unsigned short tag = memory.read<unsigned short>(gameobject + 0x54);

			if (tag == PLAYER_TAG)
			{
				temp_player_list.push_back(memory.read<uintptr_t>(object + 0x10));
			}
			else
			{
				uintptr_t object_class = memory.read<uintptr_t>(gameobject + 0x30);
				uintptr_t entity = memory.read<uintptr_t>(object_class + 0x18);
				uintptr_t transform = memory.read<uintptr_t>(object_class + 0x08);
				prefab_t prefab_entity = prefab_t(entity, transform, gameobject);
				temp_prefab_list.push_back(prefab_entity);
			}
		}
		
		player_list = temp_player_list;
		temp_player_list.clear();

		prefab_list = temp_prefab_list;
		temp_prefab_list.clear();
	}

	bool setup()
	{
		/* set game camera position */
		camera.set_position(memory.read<Vector3>(camera.get_object() + 0x42c));

		/* set game view matrix */
		camera.set_vmatrix(memory.read<vmatrix_t>(camera.get_object() + 0x2e4));

		return camera.get_position().is_valid();
	}

	void prefab_loop()
	{
		for (const auto& prefab : prefab_list)
		{
			Vector2 screen{};
			if (world_to_screen(prefab.position, screen))
			{
				/*
				*	heres where i render stuff for it
				*/
			}
		}
	}

	void player_loop()
	{
		for (const auto& entity : player_list)
		{
			BasePlayer* player = memory.read<BasePlayer*>(entity + 0x28);

			if (!player)
				continue;

			if (player->getDistance(camera.get_position()) > 300)
				continue;

			if (player->isDead())
				continue;

			if (player->isLocalPlayer())
			{
				players.local = player;
				globals.weapon_name = players.local->getHeldItem()->itemDefinition()->getDisplayName();

				/*
				*	administrator flags
				*/
				if (!player->hasFlag(BasePlayer::Flags::IsAdmin))
					player->setFlag(BasePlayer::Flags::IsAdmin);

				/*
				*	makes us able to shoot in a minicopter
				*	make sure you alt look to shoot someone
				*	as you cannot change your viewangles
				*/
				if (players.local->modelState()->hasFlag(ModelState::Flags::Mounted))
					players.local->mounted()->setCanHoldItems(true);


				if (players.local->getHeldItem()->isValid())
				{
					players.local->getHeldItem()->baseProjectile()->noSpread();
					
					players.local->getHeldItem()->baseProjectile()->pushToMap();

					/*
					*	readd the commented stuff
					*/
					//if (no_recoil)
					{
						players.local->getHeldItem()->baseProjectile()->unsetRecoil();
						players.local->getHeldItem()->baseProjectile()->noRecoil();
					}
					//else
					//{
					//	players.local->getHeldItem()->baseProjectile()->restoreRecoil();
					//}
				}

				continue;
			}
			else
			{
				bounding_box_t box = player->getBoundingBox();

				if (!box.foot_screen.x || !box.foot_screen.y || !box.head_screen.x || !box.head_screen.y)
					continue;

				/*
				*	deleted
				*/
			}
		}
	}
} entity_list;