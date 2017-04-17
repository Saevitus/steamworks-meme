#include <Windows.h> // for va_start, va_end
#include "../Header Files/Utilities.h"

void Utilities::Log(std::string strFmt, ...)
{
	if (strFmt.empty()) return;

	va_list list;

	char Buffer[512] = { 0 };

	va_start(list, strFmt);
	_vsnprintf_s(Buffer + strlen(Buffer), sizeof(Buffer), sizeof(Buffer) - strlen(Buffer), strFmt.c_str(), list);
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

void Memeworks::SetName(std::string strName)
{
	Utilities::Log("Setting name to: %s", strName.c_str());
	SteamFriends()->SetPersonaName(strName.c_str());
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

void Memeworks::SetPoorPresence(std::string strStatus, std::string strScore)
{
	Utilities::Log("Setting Status to: %s", strStatus.c_str());
	SteamFriends()->SetRichPresence("status", strStatus.c_str());
	SteamFriends()->SetRichPresence("game:act", "offline");
	SteamFriends()->SetRichPresence("game:mode", "competitive");
	SteamFriends()->SetRichPresence("game:mapgroupname", "mg_active");
	SteamFriends()->SetRichPresence("game:map", "random");
	Utilities::Log("Setting Score to: %s", strScore.c_str());
	SteamFriends()->SetRichPresence("game:score", strScore.c_str());
	SteamFriends()->SetRichPresence("game:server", "competitive");
}

bool bFirst = true;
void Memeworks::GetInternalAchievementID(int iAmount)
{
	for (int i = 0; i < iAmount; i++)
	{
		std::string strName = SteamUserStats()->GetAchievementName(i);
		if (bFirst)
		{
			Utilities::Log("Internal Achievement IDs:");
			bFirst = false;
		}
		printf("  %s\n", strName.c_str());
	}
}

void Memeworks::UnlockSingleAchievement(std::string strName)
{
	SteamUserStats()->SetAchievement(strName.c_str());
	SteamUserStats()->StoreStats();
}

void Memeworks::UnlockAchievements(int iAmount)
{
	for (int i = 0; i < iAmount; i++)
	{
		std::string strAchievement = SteamUserStats()->GetAchievementName(i);
		SteamUserStats()->SetAchievement(strAchievement.c_str());
	}
	SteamUserStats()->StoreStats();
	Utilities::Log("%i Achievement(s) Unlocked", iAmount);
}

void Memeworks::ClearAchievements(int iAmount)
{
	for (int i = 0; i < iAmount; i++)
	{
		std::string strAchievement = SteamUserStats()->GetAchievementName(i);
		SteamUserStats()->ClearAchievement(strAchievement.c_str());
	}
	SteamUserStats()->StoreStats();
}

void Memeworks::Testing::FindLobby(int iFriendIndex)
{
	int iFriend = SteamFriends()->GetFriendCount(ALL_FRIENDS);
	Utilities::Log("Friend Count: %i", iFriend);

	CSteamID FriendID = SteamFriends()->GetFriendByIndex(58, ALL_FRIENDS);
	Utilities::Log("Friend's SteamID3: [U:%i:%i]", FriendID.GetEAccountType(), FriendID.GetAccountID());

	FriendGameInfo_t pGameInfo;
	SteamFriends()->GetFriendGamePlayed(FriendID, &pGameInfo);

	CSteamID LobbyOwner = SteamMatchmaking()->GetLobbyOwner(pGameInfo.m_steamIDLobby);
	Utilities::Log("SteamID3 Of Lobby Owner: [U:%i:%i]", LobbyOwner.GetEAccountType(), LobbyOwner.GetAccountID());

	int iPlayers = SteamMatchmaking()->GetNumLobbyMembers(pGameInfo.m_steamIDLobby);
	Utilities::Log("Lobby Member Count: %i", iPlayers);

	/*for (int i = 0; i < iFriend; i++)
	{
		CSteamID FriendID = SteamFriends()->GetFriendByIndex(i, ALL_FRIENDS);
		Utilities::Log("Friend Index and Name: %i, %s", i, SteamFriends()->GetFriendPersonaName(FriendID));
	}*/
}

void Memeworks::Testing::MiscFunc1()
{
	std::string strCountry = SteamUtils()->GetIPCountry();
	Utilities::Log("Country Associated With Current IP: %s", strCountry.c_str());
	std::string strLanguage = SteamUtils()->GetSteamUILanguage();
	Utilities::Log("Current Language Being Used: %s", strLanguage.c_str());
	Utilities::Log("Is VAC Banned: %s", SteamApps()->BIsVACBanned() ? "true" : "false");
}
