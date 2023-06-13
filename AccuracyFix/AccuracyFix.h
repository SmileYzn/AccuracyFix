#pragma once

class CAccuracyFix
{
public:
	void ServerActivate();

	void CmdEnd(const edict_t* pEdict);
	bool TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
    void POST_CBasePlayer_PostThink(CBasePlayer* Player);

private:
	int m_Shooting[MAX_CLIENTS + 1];
	float m_LastFired[MAX_CLIENTS + 1];
};

extern CAccuracyFix gAccuracyFix;