#pragma once

typedef struct S_PLAYER_DATA
{
	float LastFired;
	int	  WeaponId;
} P_PLAYER_DATA, *LP_PLAYER_DATA;

class CAccuracyFix
{
public:
	void ServerActivate();

	void CmdEnd(const edict_t* pEdict);
	bool TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
    void PostThink(CBasePlayer* Player);
	float GetUserAiming(edict_t* edict, int* cpId, int* cpBody, float distance);
	cvar_t* CvarRegister(const char* Name, const char* Value);

private:
	std::map<int, P_PLAYER_DATA> m_Data;
	std::map<std::string, cvar_t> m_Cvar;

	cvar_t* m_af_accuracy_all;
	std::array<cvar_t*, MAX_WEAPONS + 1> m_af_accuracy;

	cvar_t* m_af_recoil_all;
	std::array<cvar_t*, MAX_WEAPONS + 1> m_af_recoil;

	cvar_t* m_af_distance_all;
	std::array<cvar_t*, MAX_WEAPONS + 1> m_af_distance;
};

extern CAccuracyFix gAccuracyFix;