#pragma once
#include "common.hpp"

struct weapon_info_t
{
	Vector4 recoil_value{};
	Vector4 spread_value{};
	bool automatic{};

	bool has_set_recoil = false;
	bool has_set_spread = false;
};

class drilled_t
{
private:
public:
	/* game */
	HWND rust_window = FindWindowA(NULL, _("Rust"));
	uintptr_t game_assembly = NULL;
	uintptr_t unity_player = NULL;
	uintptr_t base_networkable = NULL;

	/* screen */
	const int screen_w = GetSystemMetrics(SM_CXSCREEN);
	const int screen_h = GetSystemMetrics(SM_CYSCREEN);	
	const float screen_center_x = GetSystemMetrics(SM_CXSCREEN) / 2;
	const float screen_center_y = GetSystemMetrics(SM_CYSCREEN) / 2;

	bool menu_open = false;

	float height = 0.f;
	std::string weapon_name = _("");
	std::unordered_map<std::string, weapon_info_t> weapon_map{};
	weapon_info_t weapon_info{};
} globals;