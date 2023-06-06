#include "precompiled.h"

CAccuracyFixAttack gAccuracyFixAttack;


void CAccuracyFixAttack::PRE_CBasePlayer_PostThink(CBasePlayer* Player)
{
	if (Player->m_pActiveItem)
	{
		if (Player->m_pActiveItem->iItemSlot() == PRIMARY_WEAPON_SLOT || Player->m_pActiveItem->iItemSlot() == PISTOL_SLOT)
		{
			if (Player->pev->button & IN_ATTACK)
			{
				if (Player->CSPlayer()->m_bCanShootOverride || (Player->m_bCanShoot && g_pGameRules->IsMultiplayer() && !g_pGameRules->IsFreezePeriod() && !Player->m_bIsDefusing) || !g_pGameRules->IsMultiplayer())
				{
					CBasePlayerWeapon* Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

					if (Weapon)
					{
						switch (Player->m_pActiveItem->m_iId)
						{
							case WEAPON_P228:
							{
								this->PRE_Attack_Weapon_P228(Player, Weapon); // 
								break;
							}
							case WEAPON_SCOUT:
							{
								this->PRE_Attack_Weapon_SCOUT(Player, Weapon); //
								break;
							}
							case WEAPON_MAC10:
							{
								this->PRE_Attack_Weapon_MAC10(Player, Weapon); //
								break;
							}
							case WEAPON_AUG:
							{
								this->PRE_Attack_Weapon_AUG(Player, Weapon); //
								break;
							}
							case WEAPON_ELITE:
							{
								this->PRE_Attack_Weapon_ELITE(Player, Weapon); //
								break;
							}
							case WEAPON_FIVESEVEN:
							{
								this->PRE_Attack_Weapon_FIVESEVEN(Player, Weapon); //
								break;
							}
							case WEAPON_UMP45:
							{
								this->PRE_Attack_Weapon_UMP45(Player, Weapon); //
								break;
							}
							case WEAPON_SG550:
							{
								this->PRE_Attack_Weapon_SG550(Player, Weapon); //
								break;
							}
							case WEAPON_GALIL:
							{
								this->PRE_Attack_Weapon_GALIL(Player, Weapon); //
								break;
							}
							case WEAPON_FAMAS:
							{
								this->PRE_Attack_Weapon_FAMAS(Player, Weapon); // 
								break;
							}
							case WEAPON_USP:
							{
								this->PRE_Attack_Weapon_USP(Player, Weapon); //
								break;
							}
							case WEAPON_GLOCK18:
							{
								this->PRE_Attack_Weapon_GLOCK18(Player, Weapon); //
								break;
							}
							case WEAPON_MP5N:
							{
								this->PRE_Attack_Weapon_MP5N(Player, Weapon); //
								break;
							}
							case WEAPON_M249:
							{
								this->PRE_Attack_Weapon_M249(Player, Weapon); //
								break;
							}
							case WEAPON_M4A1:
							{
								this->PRE_Attack_Weapon_M4A1(Player, Weapon); //
								break;
							}
							case WEAPON_TMP:
							{
								this->PRE_Attack_Weapon_TMP(Player, Weapon); //
								break;
							}
							case WEAPON_G3SG1:
							{
								this->PRE_Attack_Weapon_G3SG1(Player, Weapon); //
								break;
							}
							case WEAPON_DEAGLE:
							{
								this->PRE_Attack_Weapon_DEAGLE(Player, Weapon); //
								break;
							}
							case WEAPON_SG552:
							{
								this->PRE_Attack_Weapon_SG552(Player, Weapon); //
								break;
							}
							case WEAPON_AK47:
							{
								this->PRE_Attack_Weapon_AK47(Player, Weapon); //
								break;
							}
							case WEAPON_P90:
							{
								this->PRE_Attack_Weapon_P90(Player, Weapon); //
								break;
							}
						}
					}
				}
			}
		}
	}
}

void CAccuracyFixAttack::POST_CBasePlayer_PostThink(CBasePlayer* Player)
{
	if (Player->m_pActiveItem)
	{
		if (Player->m_pActiveItem->iItemSlot() == PRIMARY_WEAPON_SLOT || Player->m_pActiveItem->iItemSlot() == PISTOL_SLOT)
		{
			if (Player->pev->button & IN_ATTACK)
			{
				if (Player->CSPlayer()->m_bCanShootOverride || (Player->m_bCanShoot && g_pGameRules->IsMultiplayer() && !g_pGameRules->IsFreezePeriod() && !Player->m_bIsDefusing) || !g_pGameRules->IsMultiplayer())
				{
					CBasePlayerWeapon* Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

					if (Weapon)
					{
						switch (Player->m_pActiveItem->m_iId)
						{
							case WEAPON_P228:
							{
								this->POST_Attack_Weapon_P228(Player, Weapon);
								break;
							}
							case WEAPON_SCOUT:
							{
								this->POST_Attack_Weapon_SCOUT(Player, Weapon);
								break;
							}
							case WEAPON_ELITE:
							{
								this->POST_Attack_Weapon_ELITE(Player, Weapon);
								break;
							}
							case WEAPON_FIVESEVEN:
							{
								this->POST_Attack_Weapon_FIVESEVEN(Player, Weapon);
								break;
							}
							case WEAPON_USP:
							{
								this->POST_Attack_Weapon_USP(Player, Weapon);
								break;
							}
							case WEAPON_GLOCK18:
							{
								this->POST_Attack_Weapon_GLOCK18(Player, Weapon);
								break;
							}
							case WEAPON_DEAGLE:
							{
								this->POST_Attack_Weapon_DEAGLE(Player, Weapon);
								break;
							}
						}
					}
				}
			}
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_P228(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (!Weapon->m_flLastFire)
	{
		if (Player->edict()->v.flags & FL_ONGROUND)
		{
			if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
			{
				if (Player->edict()->v.flags & FL_DUCKING)
				{
					this->m_flAccuracy[EntityIndex] = 1.0f;
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.95f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.90f;
			}
		}
		else
		{
			this->m_flAccuracy[EntityIndex] = 0.90f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else if (Weapon->m_iShotsFired <= 0)
	{
		this->m_flAccuracy[EntityIndex] = Weapon->m_flAccuracy;

		this->m_flAccuracy[EntityIndex] -= (0.325f - (gpGlobals->time - Weapon->m_flLastFire)) * 0.3f;
		
		if (this->m_flAccuracy[EntityIndex] < 0.6f)
		{
			this->m_flAccuracy[EntityIndex] = 0.6f;
		}
		else if (this->m_flAccuracy[EntityIndex] > 0.90f)
		{
			if (Player->edict()->v.flags & FL_ONGROUND)
			{
				if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
				{
					if (Player->edict()->v.flags & FL_DUCKING)
					{
						if (this->m_flAccuracy[EntityIndex] > 1.0f)
						{
							this->m_flAccuracy[EntityIndex] = 1.0f;
						}
					}
					else if (this->m_flAccuracy[EntityIndex] > 0.95f)
					{
						this->m_flAccuracy[EntityIndex] = 0.95f;
					}
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.90f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.90f;
			}
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		this->m_flAccuracy[EntityIndex] = -1.0f;
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_SCOUT(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (Player->edict()->v.flags & FL_DUCKING || ~Player->edict()->v.flags & FL_ONGROUND)
	{
		this->m_flAccuracy[EntityIndex] = 0.0f;
	}
	else
	{
		if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
		{
			Player->edict()->v.flags = (Player->edict()->v.flags | FL_DUCKING);

			this->m_flAccuracy[EntityIndex] = 1.0f;
		}
		else
		{
			this->m_flAccuracy[EntityIndex] = 0.0f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_MAC10(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired * ShotsFired) / 200.0f) + 0.15 + this->SmoothAccuracyTransition((ShotsFired + 1), 0.45f, 8));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 200.0f) + 0.6f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 1.65f)
		{
			this->m_flAccuracy[EntityIndex] = 1.65f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.75f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.15f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.15f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_AUG(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef  SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired * ShotsFired) / 215.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.1f, 2));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 215.0f) + 0.3f;
#endif
		if (this->m_flAccuracy[EntityIndex] > 1.0f)
		{
			this->m_flAccuracy[EntityIndex] = 1.0f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_ELITE(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (!Weapon->m_flLastFire)
	{
		if (Player->edict()->v.flags & FL_ONGROUND)
		{
			if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
			{
				if (Player->edict()->v.flags & FL_DUCKING)
				{
					this->m_flAccuracy[EntityIndex] = 1.0f;
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.94f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.88f;
			}
		}
		else
		{
			this->m_flAccuracy[EntityIndex] = 0.88f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else if (Weapon->m_iShotsFired <= 0)
	{
		this->m_flAccuracy[EntityIndex] = Weapon->m_flAccuracy;

		this->m_flAccuracy[EntityIndex] -= (0.325f - (gpGlobals->time - Weapon->m_flLastFire)) * 0.275f;

		if (this->m_flAccuracy[EntityIndex] < 0.55f)
		{
			this->m_flAccuracy[EntityIndex] = 0.55f;
		}
		else if (this->m_flAccuracy[EntityIndex] > 0.88f)
		{
			if (Player->edict()->v.flags & FL_ONGROUND)
			{
				if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
				{
					if (Player->edict()->v.flags & FL_DUCKING)
					{
						if (this->m_flAccuracy[EntityIndex] > 1.0f)
						{
							this->m_flAccuracy[EntityIndex] = 1.0f;
						}
					}
					else if (this->m_flAccuracy[EntityIndex] > 0.94f)
					{
						this->m_flAccuracy[EntityIndex] = 0.94f;
					}
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.88f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.88f;
			}
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		this->m_flAccuracy[EntityIndex] = -1.0f;
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_FIVESEVEN(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (!Weapon->m_flLastFire)
	{
		if (Player->edict()->v.flags & FL_ONGROUND)
		{
			if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
			{
				if (Player->edict()->v.flags & FL_DUCKING)
				{
					this->m_flAccuracy[EntityIndex] = 1.0f;
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.96f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.92f;
			}
		}
		else
		{
			this->m_flAccuracy[EntityIndex] = 0.92f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else if (Weapon->m_iShotsFired <= 0)
	{
		this->m_flAccuracy[EntityIndex] = Weapon->m_flAccuracy;

		this->m_flAccuracy[EntityIndex] -= (0.275f - (gpGlobals->time - Weapon->m_flLastFire)) * 0.25f;

		if (this->m_flAccuracy[EntityIndex] < 0.725f)
		{
			this->m_flAccuracy[EntityIndex] = 0.725f;
		}
		else if (this->m_flAccuracy[EntityIndex] > 0.92f)
		{
			if (Player->edict()->v.flags & FL_ONGROUND)
			{
				if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
				{
					if (Player->edict()->v.flags & FL_DUCKING)
					{
						if (this->m_flAccuracy[EntityIndex] > 1.0f)
						{
							this->m_flAccuracy[EntityIndex] = 1.0f;
						}
					}
					else if (this->m_flAccuracy[EntityIndex] > 0.96f)
					{
						this->m_flAccuracy[EntityIndex] = 0.96f;
					}
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.92f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.92f;
			}
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		this->m_flAccuracy[EntityIndex] = -1.0f;
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_UMP45(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired) / 210.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.3f, 5));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 210.0f) + 0.5f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 1.0f)
		{
			this->m_flAccuracy[EntityIndex] = 1.0f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_SG550(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (!Weapon->m_flLastFire)
	{
		if (Player->edict()->v.flags & FL_ONGROUND)
		{
			if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
			{
				if (Player->edict()->v.flags & FL_DUCKING)
				{
					this->m_flAccuracy[EntityIndex] = 1.0f;
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.99f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.98f;
			}
		}
		else
		{
			this->m_flAccuracy[EntityIndex] = 0.98f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else if (Weapon->m_iShotsFired <= 0)
	{
		this->m_flAccuracy[EntityIndex] = (0.65f + (gpGlobals->time - Weapon->m_flLastFire)) * 0.725f;

		if (this->m_flAccuracy[EntityIndex] > 0.98f)
		{
			if (Player->edict()->v.flags & FL_ONGROUND)
			{
				if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
				{
					if (Player->edict()->v.flags & FL_DUCKING)
					{
						if (this->m_flAccuracy[EntityIndex] > 1.0f)
						{
							this->m_flAccuracy[EntityIndex] = 1.0f;
						}
					}
					else if (this->m_flAccuracy[EntityIndex] > 0.99f)
					{
						this->m_flAccuracy[EntityIndex] = 0.99f;
					}
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.98f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.98f;
			}
		}
		else if (this->m_flAccuracy[EntityIndex] < 0.5f)
		{
			this->m_flAccuracy[EntityIndex] = 0.5f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_GALIL(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired * ShotsFired) / 200.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.15f, 4));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 200.0f) + 0.35f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 1.25f)
		{
			this->m_flAccuracy[EntityIndex] = 1.25f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_FAMAS(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired * ShotsFired) / 215.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.1f, 2));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 215.0f) + 0.3f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 1.0f)
		{
			this->m_flAccuracy[EntityIndex] = 1.0f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_USP(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (!Weapon->m_flLastFire)
	{
		if (Player->edict()->v.flags & FL_ONGROUND)
		{
			if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
			{
				if (Player->edict()->v.flags & FL_DUCKING)
				{
					this->m_flAccuracy[EntityIndex] = 1.0f;
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.96f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.92f;
			}
		}
		else
		{
			this->m_flAccuracy[EntityIndex] = 0.92f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else if (Weapon->m_iShotsFired <= 0)
	{
		this->m_flAccuracy[EntityIndex] = Weapon->m_flAccuracy;

		this->m_flAccuracy[EntityIndex] -= (0.3f - (gpGlobals->time - Weapon->m_flLastFire)) * 0.275f;

		if (this->m_flAccuracy[EntityIndex] < 0.6f)
		{
			this->m_flAccuracy[EntityIndex] = 0.6f;
		}
		else if (this->m_flAccuracy[EntityIndex] > 0.92f)
		{
			if (Player->edict()->v.flags & FL_ONGROUND)
			{
				if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
				{
					if (Player->edict()->v.flags & FL_DUCKING)
					{
						if (this->m_flAccuracy[EntityIndex] > 1.0f)
						{
							this->m_flAccuracy[EntityIndex] = 1.0f;
						}
					}
					else if (this->m_flAccuracy[EntityIndex] > 0.96f)
					{
						this->m_flAccuracy[EntityIndex] = 0.96f;
					}
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.92f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.92f;
			}
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		this->m_flAccuracy[EntityIndex] = -1.0f;
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_GLOCK18(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (!Weapon->m_flLastFire)
	{
		if (Player->edict()->v.flags & FL_ONGROUND)
		{
			if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
			{
				if (Player->edict()->v.flags & FL_DUCKING)
				{
					this->m_flAccuracy[EntityIndex] = 1.0f;
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.95f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.90f;
			}
		}
		else
		{
			this->m_flAccuracy[EntityIndex] = 0.90f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else if (Weapon->m_iShotsFired <= 0)
	{
		this->m_flAccuracy[EntityIndex] = Weapon->m_flAccuracy;

		this->m_flAccuracy[EntityIndex] -= (0.325f - (gpGlobals->time - Weapon->m_flLastFire)) * 0.275f;

		if (this->m_flAccuracy[EntityIndex] < 0.6f)
		{
			this->m_flAccuracy[EntityIndex] = 0.6f;
		}
		else if (this->m_flAccuracy[EntityIndex] > 0.90f)
		{
			if (Player->edict()->v.flags & FL_ONGROUND)
			{
				if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
				{
					if (Player->edict()->v.flags & FL_DUCKING)
					{
						if (this->m_flAccuracy[EntityIndex] > 1.0f)
						{
							this->m_flAccuracy[EntityIndex] = 1.0f;
						}
					}
					else if (this->m_flAccuracy[EntityIndex] > 0.95f)
					{
						this->m_flAccuracy[EntityIndex] = 0.95f;
					}
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.90f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.90f;
			}
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		this->m_flAccuracy[EntityIndex] = -1.0f;
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_MP5N(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired) / 220.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.25f, 5));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired) / 220.0f) + 0.45f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 0.75f)
		{
			this->m_flAccuracy[EntityIndex] = 0.75f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_M249(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired * ShotsFired) / 175.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.2f, 4));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 175.0f) + 0.4f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 0.9f)
		{
			this->m_flAccuracy[EntityIndex] = 0.9f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_M4A1(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired * ShotsFired) / 220.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.15f, 3));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 220.0f) + 0.35f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 1.25f)
		{
			this->m_flAccuracy[EntityIndex] = 1.25f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_TMP(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired * ShotsFired) / 220.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.35f, 7));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 220.0f) + 0.55f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 1.4f)
		{
			this->m_flAccuracy[EntityIndex] = 1.4f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_G3SG1(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{

}

void CAccuracyFixAttack::PRE_Attack_Weapon_DEAGLE(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (!Weapon->m_flLastFire)
	{
		if (Player->edict()->v.flags & FL_ONGROUND)
		{
			if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
			{
				if (Player->edict()->v.flags & FL_DUCKING)
				{
					this->m_flAccuracy[EntityIndex] = 1.0f;
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.96f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.92f;
			}
		}
		else
		{
			this->m_flAccuracy[EntityIndex] = 0.92f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else if (Weapon->m_iShotsFired <= 0)
	{
		this->m_flAccuracy[EntityIndex] = Weapon->m_flAccuracy;

		this->m_flAccuracy[EntityIndex] -= (0.4f - (gpGlobals->time - Weapon->m_flLastFire)) * 0.35f;

		if (this->m_flAccuracy[EntityIndex] < 0.55f)
		{
			this->m_flAccuracy[EntityIndex] = 0.55f;
		}
		else if (this->m_flAccuracy[EntityIndex] > 0.92f)
		{
			if (Player->edict()->v.flags & FL_ONGROUND)
			{
				if (!Player->edict()->v.velocity[0] && !Player->edict()->v.velocity[1])
				{
					if (Player->edict()->v.flags & FL_DUCKING)
					{
						if (this->m_flAccuracy[EntityIndex] > 1.0f)
						{
							this->m_flAccuracy[EntityIndex] = 1.0f;
						}
					}
					else if (this->m_flAccuracy[EntityIndex] > 0.96f)
					{
						this->m_flAccuracy[EntityIndex] = 0.96f;
					}
				}
				else
				{
					this->m_flAccuracy[EntityIndex] = 0.92f;
				}
			}
			else
			{
				this->m_flAccuracy[EntityIndex] = 0.92f;
			}
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		this->m_flAccuracy[EntityIndex] = -1.0f;
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_SG552(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired * ShotsFired) / 220.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.1f, 3));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 220.0f) + 0.3f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 1.0f)
		{
			this->m_flAccuracy[EntityIndex] = 1.0f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_AK47(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired * ShotsFired) / 200.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.15, 3));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 200.0f) + 0.35f;
#endif
		if (this->m_flAccuracy[EntityIndex] > 1.25f)
		{
			this->m_flAccuracy[EntityIndex] = 1.25f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_P90(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

#ifdef SMOOTH_SPREAD_TRANSITION
		this->m_flAccuracy[EntityIndex] = (((ShotsFired * ShotsFired) / 175.0f) + 0.2f + this->SmoothAccuracyTransition((ShotsFired + 1), 0.25f, 6));
#else
		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired) / 175.0f) + 0.45f;
#endif

		if (this->m_flAccuracy[EntityIndex] > 1.0f)
		{
			this->m_flAccuracy[EntityIndex] = 1.0f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::POST_Attack_Weapon_P228(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (this->m_flAccuracy[EntityIndex] > 0.90f)
	{
		Weapon->m_flAccuracy = 0.90f;
	}
	else if (this->m_flAccuracy[EntityIndex] > 0.0f)
	{
		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
}

void CAccuracyFixAttack::POST_Attack_Weapon_SCOUT(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (this->m_flAccuracy[EntityIndex])
	{
		Player->edict()->v.flags = (Player->edict()->v.flags & ~FL_DUCKING);
	}
}

void CAccuracyFixAttack::POST_Attack_Weapon_ELITE(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (this->m_flAccuracy[EntityIndex] > 0.88f)
	{
		Weapon->m_flAccuracy = 0.88f;
	}
	else if (this->m_flAccuracy[EntityIndex] > 0.0f)
	{
		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
}

void CAccuracyFixAttack::POST_Attack_Weapon_FIVESEVEN(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (this->m_flAccuracy[EntityIndex] > 0.92f)
	{
		Weapon->m_flAccuracy = 0.92f;
	}
	else if (this->m_flAccuracy[EntityIndex] > 0.0f)
	{
		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
}

void CAccuracyFixAttack::POST_Attack_Weapon_USP(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (this->m_flAccuracy[EntityIndex] > 0.92f)
	{
		Weapon->m_flAccuracy = 0.92f;
	}
	else if (this->m_flAccuracy[EntityIndex] > 0.0f)
	{
		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
}

void CAccuracyFixAttack::POST_Attack_Weapon_GLOCK18(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (this->m_flAccuracy[EntityIndex] > 0.90f)
	{
		Weapon->m_flAccuracy = 0.90f;
	}
	else if (this->m_flAccuracy[EntityIndex] > 0.0f)
	{
		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
}

void CAccuracyFixAttack::POST_Attack_Weapon_DEAGLE(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	auto EntityIndex = Player->entindex();

	if (this->m_flAccuracy[EntityIndex] > 0.92f)
	{
		Weapon->m_flAccuracy = 0.92f;
	}
	else if (this->m_flAccuracy[EntityIndex] > 0.0f)
	{
		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
	}
}
