#include <Windows.h> // for va_start, va_end
#include "../Header Files/Utilities.h"

void Utilities::Log(const char* fmt, ...)
{
	if (!fmt) return;

	va_list list;

	char Buffer[512] = { 0 };

	va_start(list, fmt);
	_vsnprintf_s(Buffer + strlen(Buffer), sizeof(Buffer), sizeof(Buffer) - strlen(Buffer), fmt, list);
	va_end(list);

	if (Buffer[0] != '\0')
	{
		printf("[LOG]: %s\n", Buffer);
	}
}

void Memeworks::GetSteamID3()
{
	CSteamID steamID = SteamUser()->GetSteamID();
	Utilities::Log("SteamID3: [U:%i:%i]", steamID.GetEAccountType(), steamID.GetAccountID());
}

void Memeworks::SetName(const char* pchName)
{
	Utilities::Log("Setting name to: %s", pchName);
	SteamFriends()->SetPersonaName(pchName);
}

void Memeworks::GetSteamLevel()
{
	int iSteamLevel = SteamUser()->GetPlayerSteamLevel();
	Utilities::Log("Steam Level: %i", iSteamLevel);
}

void Memeworks::GetFriendCount(int iFriendFlags)
{
	int iFriend = SteamFriends()->GetFriendCount(iFriendFlags);
	Utilities::Log("Friend Count: %i", iFriend);
}

void Memeworks::SetPoorPresence(const char* pchStatus, const char* pchScore)
{
	Utilities::Log("Setting Status to: %s", pchStatus);
	SteamFriends()->SetRichPresence("status", pchStatus);
	SteamFriends()->SetRichPresence("game:act", "offline");
	SteamFriends()->SetRichPresence("game:mode", "competitive");
	SteamFriends()->SetRichPresence("game:mapgroupname", "mg_active");
	SteamFriends()->SetRichPresence("game:map", "random");
	Utilities::Log("Setting Score to: %s", pchScore);
	SteamFriends()->SetRichPresence("game:score", pchScore);
	SteamFriends()->SetRichPresence("game:server", "competitive");
}

void Memeworks::UnlockAchievements(int iAmount)
{
	for (int i = 0; i < iAmount; i++)
	{
		const char* pchAchievement = SteamUserStats()->GetAchievementName(i);
		SteamUserStats()->SetAchievement(pchAchievement);
	}
	SteamUserStats()->StoreStats();
}

void Memeworks::ClearAchievements(int iAmount)
{
	for (int i = 0; i < iAmount; i++)
	{
		const char* pchAchievement = SteamUserStats()->GetAchievementName(i);
		SteamUserStats()->ClearAchievement(pchAchievement);
	}
	SteamUserStats()->StoreStats();
}
