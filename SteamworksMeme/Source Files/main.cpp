#include "../Header Files/Utilities.h"
#include "../Header Files/Memory.h"

void main()
{
	// simple steam api shit, tells us the path to steam.exe and
	// if steam is running or not
	Utilities::Log("Steam Location: %s", SteamAPI_GetSteamInstallPath());
	Utilities::Log("Steam Running: %s", SteamAPI_IsSteamRunning() ? "true" : "false");

	// all this other shit has been documented in the header files you fuckwit
	if (Memeworks::Initiated())
	{
		Utilities::Log("Requsted User Statistics: %s", Memeworks::RequestUserStats() ? "true" : "false");
		Memeworks::GetSteamID3();
		Memeworks::GetSteamLevel();
		Memeworks::GetFriendCount(ALL_FRIENDS);
		Memeworks::Testing::MiscFunc1();
		Memeworks::UnlockAchievements(520); // tf2 has 520 achievements

		/*Memory::Process proc = Memory::Process("csgo.exe");
		Memory::Module mod = proc.FindModule("client.dll");

		Utilities::Log("PID: %i", proc.GetPID());

		DWORD base = mod.GetBase();
		DWORD localplayer = proc.ReadMemory<DWORD>(base + 0xAA66D4);*/

		//Memeworks::GetInternalAchievementID(12);

		Utilities::WaitForInput();
		SteamAPI_Shutdown();

	}
}
