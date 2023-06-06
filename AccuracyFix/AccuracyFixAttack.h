#pragma once

#define SMOOTH_SPREAD_TRANSITION

class CAccuracyFixAttack
{
public:
	float SmoothAccuracyTransition(int iSteppingId, float flMaxInaccuracy, int iSteppingsMax)
	{
		if (iSteppingId >= iSteppingsMax)
		{
			return flMaxInaccuracy;
		}

		return (((float)iSteppingId * flMaxInaccuracy) / (float)iSteppingsMax);
	}

	void PRE_CBasePlayer_PostThink(CBasePlayer* Player);
	void POST_CBasePlayer_PostThink(CBasePlayer* Player);

	//
	void PRE_Attack_Weapon_P228(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_SCOUT(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_MAC10(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_AUG(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_ELITE(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_FIVESEVEN(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_UMP45(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_SG550(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_GALIL(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_FAMAS(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_USP(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_GLOCK18(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_MP5N(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_M249(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_M3(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_M4A1(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_TMP(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_G3SG1(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_DEAGLE(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_SG552(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_AK47(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void PRE_Attack_Weapon_P90(CBasePlayer* Player, CBasePlayerWeapon* Weapon);

	//
	void POST_Attack_Weapon_P228(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void POST_Attack_Weapon_SCOUT(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void POST_Attack_Weapon_ELITE(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void POST_Attack_Weapon_FIVESEVEN(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void POST_Attack_Weapon_USP(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void POST_Attack_Weapon_GLOCK18(CBasePlayer* Player, CBasePlayerWeapon* Weapon);
	void POST_Attack_Weapon_DEAGLE(CBasePlayer* Player, CBasePlayerWeapon* Weapon);

private:
	float m_flAccuracy[MAX_CLIENTS + 1];
};

extern CAccuracyFixAttack gAccuracyFixAttack;