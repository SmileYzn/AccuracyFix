#pragma once

class CAccuracyFixPunch
{
public:
	void PRE_CBasePlayer_PostThink(CBasePlayer* Player);
	void POST_CBasePlayer_PostThink(CBasePlayer* Player);

private:
	vec3_t m_vecPunchAngle[MAX_CLIENTS + 1];
};

extern CAccuracyFixPunch gAccuracyFixPunch;