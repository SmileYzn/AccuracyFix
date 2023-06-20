#pragma once

typedef struct S_PLAYER_DATA
{
	float LastFired;
	int   ShotsFired;
	int   m_TM;
	int   m_Body;
	int   m_Target;
} P_PLAYER_DATA, *LP_PLAYER_DATA;

class CAccuracyFix
{
public:
	void ServerActivate();

	void CmdEnd(const edict_t* pEdict);
	bool TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
    void PostThink(CBasePlayer* Player);
	float GetUserAiming(edict_t* edict, int* cpId, int* cpBody, float distance);

private:
	std::map<int, P_PLAYER_DATA> m_Data;
};

extern CAccuracyFix gAccuracyFix;