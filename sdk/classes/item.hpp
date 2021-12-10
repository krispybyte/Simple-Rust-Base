#pragma once
#include "../../common.hpp"

class Item
{
public:
	ItemDefinition* itemDefinition()
	{
		return memory.read<ItemDefinition*>(reinterpret_cast<uintptr_t>(this) + o::Item_info);
	}

	BaseProjectile* baseProjectile()
	{
		return memory.read<BaseProjectile*>(reinterpret_cast<uintptr_t>(this) + o::Item_heldEntity);
	}

	bool isValid()
	{
		return baseProjectile();
	}
};