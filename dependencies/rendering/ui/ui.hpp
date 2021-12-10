#pragma once
#include "../../../common.hpp"

namespace ui
{
	void initialize()
	{
		/* fonts */
		{
			ImGuiIO* io = &ImGui::GetIO();
		}

		/* images */
		{

		}
	}

	void run()
	{
		if (GetForegroundWindow() != globals.rust_window)
			return;
		
		entity_list.setup();
		entity_list.player_loop();
		entity_list.prefab_loop();

		/*
		*	deleted my GUI framework
		*	might post it onto github
		*	later on once it's finished
		*/
	}
}