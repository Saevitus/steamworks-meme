#pragma once
#include <conio.h> // needed for _getch();
#include <cstdio> // needed for printf();
#include <string> // needed for std::string
#include "steam_api.h"

#define MISC_FUNCS

// EFriendFlags
#define ALL_FRIENDS 0xFFFF

namespace Utilities
{
	// copypasta from syn, just a basic wrapper for printf();
	// using va_list
	void Log(std::string strFmt, ...);

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

	// prints the SteamID3
	void GetSteamID3();

	// well... if you don't understand xd
	void SetName(std::string strName);

	// prints your current steam level
	void GetSteamLevel();

	// gets your friend count, using the friend flags.
	// if you use k_EFriendFlagAll, from EFriendFlags(isteamfriends.h)
	// it'll display all friends, including blocked people
	// even if you don't have them added
	void GetFriendCount(int iFriendFlags);

	// sets the rich presence of your status on steam, and ingame score
	// for games like csgo, to any string you input.
	void SetPoorPresence(std::string strStatus, std::string strScore);

	// each achievement for games on steam have an internal name
	// which could be like FUCKING_KILL_ME or suicideiscool3
	// doesn't matter, either way this fucking gets them
	void GetInternalAchievementID(int iAmount);

	// to be used in conjunction with GetInternalAchievementID
	// use the internal name in this, if you want to unlock a single
	// achievement, only for current appid
	void UnlockSingleAchievement(std::string strName);

	// unlocks achievements up to the number you input
	// only for current appid
	void UnlockAchievements(int iAmount);

	// clears achievements up to the number you input
	// only for current appid
	// TODO: add custom achievement clearing
	void ClearAchievements(int iAmount);

	// testing namespace so I can stop filling
	// main() and memeworks with useless testing shit
	namespace Testing
	{
		void FindLobby(int iFriendIndex);
		
		void MiscFunc1();

	}
}
