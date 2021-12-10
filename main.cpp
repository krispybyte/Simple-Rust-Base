#include "common.hpp"

int main()
{
	SetConsoleTitleA(utils.random_lower_str(utils.random_int(12, 26)).c_str());
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

	globals.game_assembly = memory.module_base(_("GameAssembly.dll"));
	globals.unity_player = memory.module_base(_("UnityPlayer.dll"));
	globals.base_networkable = memory.read<uintptr_t>(globals.game_assembly + o::BaseNetworkable_c);

	printf(_("[*] RustClient.exe Window @ 0x%p\n"), globals.rust_window);
	printf(_("[*] GameAssembly.dll @ 0x%p\n"), globals.game_assembly);
	printf(_("[*] UnityPlayer.dll @ 0x%p\n"), globals.unity_player);

	std::thread([&]()
	{
		while (true)
		{
			entity_list.cache();
			std::this_thread::sleep_for(std::chrono::microseconds(5000));
		}
	}).detach();

	std::thread([&]()
	{
		features.run();
	}).detach();

	std::thread([&]()
	{
		aimbot.run();
	}).detach();

	return 0;
}