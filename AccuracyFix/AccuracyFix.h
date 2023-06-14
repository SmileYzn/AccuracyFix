#pragma once

class CAccuracyFix
{
public:
	void ServerActivate();

	bool TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
    void PostThink(CBasePlayer* Player);
	void SetAnimation(CBasePlayer* Player, PLAYER_ANIM playerAnim);

private:
	bool  m_Shooting[MAX_CLIENTS + 1];
};

extern CAccuracyFix gAccuracyFix;