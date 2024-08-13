#pragma once

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
};

extern CAccuracyFix gAccuracyFix;
