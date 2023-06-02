#pragma once

class CAccuracyFix
{
public:
	void PRE_SetAnimation(CBasePlayer* Player, PLAYER_ANIM playerAnim);
	void POST_SetAnimation(CBasePlayer* Player, PLAYER_ANIM playerAnim);

	void PRE_Weapon_AK47(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Weapon_M4A1(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
private:
	float m_fAccuracy = 0;
};

extern CAccuracyFix gAccuracyFix;