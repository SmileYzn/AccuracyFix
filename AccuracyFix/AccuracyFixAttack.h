#pragma once

class CAccuracyFixAttack
{
public:
	void PRE_CBasePlayer_PostThink(CBasePlayer* Player);
	void POST_CBasePlayer_PostThink(CBasePlayer* Player);

	// 
	void PRE_Attack_Weapon_AK47(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_M4A1(CBasePlayer* Player, CBasePlayerWeapon* Weapon);

private:
	float m_flAccuracy[MAX_CLIENTS + 1];
};

extern CAccuracyFixAttack gAccuracyFixAttack;