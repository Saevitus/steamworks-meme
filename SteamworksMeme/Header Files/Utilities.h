#pragma once
#include <conio.h> // needed for _getch();
#include <cstdio> // needed for printf();
#include "steam_api.h"

// EFriendFlags
#define ALL_FRIENDS 0xFFFF

namespace Utilities
{
	// copypasta from syn, just a basic wrapper for printf();
	// using va_list
	void Log(const char* fmt, ...);

	// basically does the same as system("pause");
	// just gets input inside the console window, and will exit the program.
	// inline because it'd be a waste of my time to do it in a source file
	inline void WaitForInput() { while (!_getch()); }
}

namespace Memeworks
{
	// initializes steam api
	// inline because it'd be a waste of my time to do it in a source file
	inline bool Initiated() { return SteamAPI_Init(); }

	// requests user statistics
	// inline because it'd be a waste of my time to do it in a source file
	inline bool RequestUserStats() { return  SteamUserStats()->RequestCurrentStats(); }

	// prints the SteamID3 of the account currently logged in
	void GetSteamID3();

	// well... if you don't understand xd
	void SetName(const char* pchName);

	// prints your current steam level
	void GetSteamLevel();

	// gets your friend count, using the friend flags.
	// if you use k_EFriendFlagAll, from EFriendFlags(isteamfriends.h)
	// it'll display all friends, including blocked people
	// even if you don't have them added
	void GetFriendCount(int iFriendFlags);

	// sets the rich presence of your status on steam, and ingame score
	// for games like csgo, to any string you input.
	void SetPoorPresence(const char* pchStatus, const char* pchScore);

	// unlocks achievements up to the number you input
	// only for current appid
	// TODO: add custom achievement unlocking
	void UnlockAchievements(int iAmount);

	// clears achievements up to the number you input
	// only for current appid
	// TODO: add custom achievement clearing
	void ClearAchievements(int iAmount);
}
