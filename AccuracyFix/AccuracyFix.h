#pragma once

class CAccuracyFix
{
public:
	void PRE_UpdateClientData(CBasePlayer* Player);
	void POST_UpdateClientData(CBasePlayer* Player);

	void PRE_Weapon_AK47(CBasePlayer* Player, CBasePlayerWeapon* Weapon);

private:
	float m_fAccuracy = 0;
};

extern CAccuracyFix gAccuracyFix;