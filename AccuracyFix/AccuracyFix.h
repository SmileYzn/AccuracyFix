#pragma once

typedef struct S_USER_DATA
{
    int     m_Shooting;
    int     m_TM;
    int     m_Body;
    int     m_Target;
} P_USER_DATA, *LP_USER_DATA;

class CAccuracyFix
{
public:
	void ServerActivate();

	bool TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
    void POST_CBasePlayer_PostThink(CBasePlayer* Player);
    float GetUserAiming(edict_t* edict, int* cpId, int* cpBody, float distance);

private:
	std::map<int, P_USER_DATA> m_Player;
};

extern CAccuracyFix gAccuracyFix;