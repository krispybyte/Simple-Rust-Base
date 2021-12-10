#pragma once
#include "../../common.hpp"

/*
*	TODO:
*	- change { 0.f, 0.f, 0.f, 0.f } inside noRecoil function
*	  to the slider value's we will have in the menu (X, Y)
*	- add noSpread resetting
*/

struct bullet_info
{
	float velocity = 333;
	float drag = 1.f;
	float gravity = 1.f;
	float velocity_scale = 1.f;
	float velocity_scalar = 1.f;
};

struct ProjectileWeaponModModifier
{
	bool enabled;
	float scalar;
	float offset;
};

class BaseProjectile
{
public:
	void noRecoil()
	{
		/* check if we already set recoil values for this name in the map */
		if (!globals.weapon_map[globals.weapon_name].has_set_recoil)
		{
			/* get our recoil properties */
			uintptr_t recoil_properties = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + o::BaseProjectile_recoil);
			
			/* read our recoil values */
			Vector4 recoil_values = memory.read<Vector4>(recoil_properties + o::RecoilProperties_recoilYawMin);

			/* check if values have already been set, if not then we know the values are the original ones */
			if (recoil_values != Vector4{0.f, 0.f, 0.f, 0.f})
				globals.weapon_map[globals.weapon_name].recoil_value = recoil_values;

			/* set no recoil */
			memory.write<Vector4>(recoil_properties + 0x18, { 0.f, 0.f, 0.f, 0.f });

			/* know we have set the recoil for this name so that we don't do it again until unset */
			globals.weapon_map[globals.weapon_name].has_set_recoil = true;
		}
	}

	void noSpread()
	{
		/* check if we already set spread for this name in the map */
		if (!globals.weapon_map[globals.weapon_name].has_set_spread)
		{
			/* save the values before modifying it */
			globals.weapon_map[globals.weapon_name].spread_value = memory.read<Vector4>(reinterpret_cast<uintptr_t>(this) + o::BaseProjectile_aimCone);
			
			/* set no spread */
			memory.write<Vector4>(reinterpret_cast<uintptr_t>(this) + o::BaseProjectile_aimCone, { -3.f, -3.f, -3.f, -3.f });
			
			/* know we have set the spread for this name so that we don't do it again until unset */
			globals.weapon_map[globals.weapon_name].has_set_spread = true;
		}
	}

	void pushToMap()
	{
		/* add weapon name if it doesn't already exist in the map */
		if (globals.weapon_map.count(globals.weapon_name) <= 0)
			globals.weapon_map[globals.weapon_name] = globals.weapon_info;
	}

	void restoreRecoil()
	{
		/* if recoil has been set ( { 0.f, 0.f, 0.f, 0.f } )*/
		if (globals.weapon_map[globals.weapon_name].has_set_recoil)
		{
			uintptr_t recoil_properties = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + o::BaseProjectile_recoil);
			/* then set it back to the original values we stored */
			memory.write<Vector4>(recoil_properties + o::RecoilProperties_recoilYawMin, globals.weapon_map[globals.weapon_name].recoil_value);
		}
	}

	void unsetRecoil()
	{
		/* set to false, this will make the noRecoil run if this was set to true earlier */
		globals.weapon_map[globals.weapon_name].has_set_recoil = false;
	}

	bool isAiming()
	{
		return memory.read<bool>(reinterpret_cast<uintptr_t>(this) + o::BaseProjectile_aiming);
	}

	bool isReloading()
	{
		return memory.read<bool>(reinterpret_cast<uintptr_t>(this) + o::BaseProjectile_isReloading);
	}

	int getMagazineCapacity()
	{
		uintptr_t magazine = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + o::BaseProjectile_primaryMagazine);
		return memory.read<int>(magazine + o::Magazine_capacity);
	}

	int getMagazineSize()
	{
		uintptr_t magazine = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + o::BaseProjectile_primaryMagazine);
		return memory.read<int>(magazine + o::Magazine_contents);
	}

	bullet_info getBulletInfo()
	{
		bullet_info info{};

		info.velocity_scale = memory.read<float>(reinterpret_cast<uintptr_t>(this) + 0x284);

		uintptr_t magazine = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + o::BaseProjectile_primaryMagazine);
		uintptr_t unity_class = memory.read_chain<uintptr_t>(magazine, { 0x20, 0x10, 0x30 });
		uintptr_t itemModProjectile = utils.get_component(unity_class, _("ItemModProjectile"));

		info.velocity = memory.read<float>(itemModProjectile + 0x34);

		uintptr_t projectileObject = memory.read<uintptr_t>(itemModProjectile + 0x18);

		uintptr_t unk0 = memory.read<uintptr_t>(projectileObject + 0x18);
		uintptr_t unk1 = memory.read<uintptr_t>(unk0 + 0x10);

		uintptr_t projectile = utils.get_component(unk1, _("Projectile"));

		Vector2 projectile_info = memory.read<Vector2>(projectile + 0x24);

		info.drag = projectile_info.x;
		info.gravity = projectile_info.y;

		uintptr_t children_list = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x40);

		int children_list_size = memory.read<int>(children_list + 0x18);
		children_list = memory.read<uintptr_t>(children_list + 0x10);

		for (int i = 0; i < children_list_size; ++i)
		{
			uintptr_t child_entity = memory.read<uintptr_t>(children_list + (0x20 + (i * 0x8)));
			std::string child_entity_name = memory.read_str(memory.read<uintptr_t>(child_entity + 0x10));

			if (child_entity_name == _("ProjectileWeaponMod"))
			{
				ProjectileWeaponModModifier velocity_scalar = memory.read<ProjectileWeaponModModifier>((child_entity + 0x178));

				if (velocity_scalar.enabled)
					info.velocity_scalar = velocity_scalar.scalar;
			}
		}

		return info;
	}
};