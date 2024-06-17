#pragma once

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
typedef struct S_PLAYER_DATA
{
	float LastFired;
	int	  WeaponId;
} P_PLAYER_DATA, *LP_PLAYER_DATA;
#endif

class CAccuracyFix
{
public:
	void ServerActivate();

	void CmdEnd(const edict_t* pEdict);
	void TraceLine(const float* vStart, const float* vEnd, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
    void PostThink(CBasePlayer* Player);

private:
	cvar_t* m_af_distance_all;
	std::array<cvar_t*, MAX_WEAPONS + 1> m_af_distance;

	cvar_t* m_af_accuracy_all;
	std::array<cvar_t*, MAX_WEAPONS + 1> m_af_accuracy;

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
	std::map<int, P_PLAYER_DATA> m_Data;

	cvar_t* m_af_recoil_all;
	std::array<cvar_t*, MAX_WEAPONS + 1> m_af_recoil;
#endif
};

extern CAccuracyFix gAccuracyFix;
