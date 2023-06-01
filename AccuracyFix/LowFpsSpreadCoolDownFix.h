#pragma once

typedef struct S_SHOT_FIX_DATA
{
	float GameTime;
	float Delay;
	int DecreaseCount;

	int ShotsFired;
	float DecreaseShotsFired;

	int OldShotsFired;
	float OldDecreaseShotsFired;

	void Reset()
	{
		this->GameTime = 0.0f;
		this->Delay = 0.0f;
		this->DecreaseCount = 0;

		this->ShotsFired = 0;
		this->DecreaseShotsFired = 0.0f;

		this->OldShotsFired = 0;
		this->OldDecreaseShotsFired = 0.0f;
	}

} P_SHOTS_FIX_DATA, *LP_SHOTS_FIX_DATA;

class CLowFpsSpreadCoolDownFix
{
public:
	void ServerActivate();

	void PRE_PostThink(CBasePlayer* Player);
	void POST_PostThink(CBasePlayer* Player);

private:
	P_SHOTS_FIX_DATA m_Data[MAX_CLIENTS + 1];
};

extern CLowFpsSpreadCoolDownFix gLowFpsSpreadCoolDownFix;