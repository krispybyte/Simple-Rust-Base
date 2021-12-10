#pragma once
#include "../../common.hpp"

class ItemDefinition
{
public:
	std::string getShortname()
	{
		uintptr_t nameptr = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x20);
		std::wstring shortname = memory.read_wstr(nameptr + 0x14);
		return std::string(shortname.begin(), shortname.end());
	}

	std::string getDisplayName()
	{
		uintptr_t translation = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x28);
		uintptr_t nameptr = memory.read<uintptr_t>(translation + 0x18);
		std::wstring shortname = memory.read_wstr(nameptr + 0x14);
		
		// shotgun filter
		{
			std::wstring shotgun_filter = _(L" Shotgun");
			size_t shotgun_pos = shortname.find(shotgun_filter);
			if (shotgun_pos != std::string::npos)
				shortname.erase(shotgun_pos, shotgun_filter.length());
		}
		// shorten some names more
		{
			std::wstring automatic_filter = _(L"Automatic "); // so we can keep 'semi-rifle', 'semi-pistol', etc...
			size_t automatic_pos = shortname.find(automatic_filter);
			if (automatic_pos != std::string::npos)
				shortname.erase(automatic_pos, automatic_filter.length());
		
			std::wstring lr_300_filter = _(L"LR-300 Assault Rifle"); // shorten to 'LR-300'
			size_t lr_300_pos = shortname.find(lr_300_filter);
			if (lr_300_pos != std::string::npos)
				shortname = _(L"LR-300");
		}
		
		return (shortname.length() > 128 || shortname.empty()) ? _("None") : std::string(shortname.begin(), shortname.end());
	}
};