#include "Utilities.h"

void main()
{
	Utilities::Log("Steam Location: %s", SteamAPI_GetSteamInstallPath());
	Utilities::Log("Steam Running: %s", SteamAPI_IsSteamRunning() ? "true" : "false");

	if (Memeworks::Initiated())
	{
		Utilities::Log("Requsted User Statistics: %s", Memeworks::RequestUserStats() ? "true" : "false");
		Memeworks::GetSteamID3();
		Memeworks::SetName("meme");
		Memeworks::GetSteamLevel();
		Memeworks::GetFriendCount(ALL_FRIENDS);
		Memeworks::UnlockAchievements(127); // 167(678)
		//Memeworks::ClearAchievements(167);
		Memeworks::SetPoorPresence("fuck I love memes", "payhack.net ~ payhack.net ~ payhack.net ~ payhack.net ~ payhack.net");

		Utilities::WaitForInput();
		SteamAPI_Shutdown();

	}
}
