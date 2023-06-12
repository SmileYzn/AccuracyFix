#pragma once

typedef struct S_USER_DATA
{
    float  m_LastFired;
    vec3_t m_PunchAngle;
    bool  m_Shooting;
    int   m_TM;
    int   m_Body;
    int   m_Target;
} P_USER_DATA, *LP_USER_DATA;

class CAccuracyFix
{
public:
	void ServerActivate();

	void CmdEnd(const edict_t* player);
	void TraceLine(const float* starn, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
    void POST_CBasePlayer_PostThink(CBasePlayer* Player);
    float GetUserAiming(edict_t* edict, int* cpId, int* cpBody, float distance);

private:
	std::map<int, P_USER_DATA> m_Player;
};

extern CAccuracyFix gAccuracyFix;