#pragma once
#include "../../common.hpp"
#include <codecvt>

class utils_t
{
public:
	std::string random_str(size_t length)
	{
		auto randchar = []() -> char
		{
			const char charset[] =
			{
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz"
			};

			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		return str;
	}

	std::string random_lower_str(size_t length)
	{
		auto randchar = []() -> char
		{
			const char charset[] =
			{
				"0123456789"
				"abcdefghijklmnopqrstuvwxyz"
			};

			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		return str;
	}

	int random_int(int min, int max)
	{
		static bool first = true;
		if (first)
		{
			srand((unsigned int)time(NULL));
			first = false;
		}
		return min + rand() % ((max + 1) - min);
	}

	bool is_running(const char* name)
	{
		return FindWindowA(NULL, name);
	}

	uintptr_t get_component(uintptr_t game_object, const char* name_str)
	{
		if (!game_object)
			return NULL;

		uintptr_t list = memory.read<uintptr_t>(game_object + 0x30);
		for (int i = 0; i < 20; i++)
		{
			uintptr_t component = memory.read<uintptr_t>(list + (0x10 * i + 0x8));

			if (!component)
				continue;

			uintptr_t unk1 = memory.read<uintptr_t>(component + 0x28);

			if (!unk1)
				continue;

			uintptr_t name_ptr = memory.read<uintptr_t>(unk1);
			std::string name = memory.read_str(memory.read<uintptr_t>(name_ptr + 0x10), 18);

			if (!strcmp(name.c_str(), name_str))
				return unk1;
		}

		return NULL;
	}
} utils;