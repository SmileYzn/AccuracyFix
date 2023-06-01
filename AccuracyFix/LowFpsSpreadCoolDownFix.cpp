#include "precompiled.h"

CLowFpsSpreadCoolDownFix gLowFpsSpreadCoolDownFix;

void CLowFpsSpreadCoolDownFix::ServerActivate()
{
	for (int i = 0; i <= gpGlobals->maxClients; i++)
	{
		this->m_Data[i].Reset();
	}
}

void CLowFpsSpreadCoolDownFix::PRE_PostThink(CBasePlayer* Player)
{
	if (Player->IsAlive() && !Player->m_pTank)
	{
		if (Player->m_pActiveItem)
		{
			if (Player->m_pActiveItem->IsWeapon())
			{
				auto EntityIndex = Player->entindex();

				if (Player->pev->button & IN_ATTACK)
				{
					this->m_Data[EntityIndex].OldShotsFired = 0;
					this->m_Data[EntityIndex].OldDecreaseShotsFired = 0.0f;
				}
				else
				{
					CBasePlayerWeapon* Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

					if (Weapon)
					{
						this->m_Data[EntityIndex].OldDecreaseShotsFired = Weapon->m_flDecreaseShotsFired;

						if (this->m_Data[EntityIndex].OldDecreaseShotsFired < gpGlobals->time)
						{
							this->m_Data[EntityIndex].OldShotsFired = Weapon->m_iShotsFired;
						}
					}
				}
			}
		}
	}
}

void CLowFpsSpreadCoolDownFix::POST_PostThink(CBasePlayer* Player)
{
	if (Player->IsAlive() && !Player->m_pTank)
	{
		if (Player->m_pActiveItem)
		{
			if (Player->m_pActiveItem->IsWeapon())
			{
				auto EntityIndex = Player->entindex();

				CBasePlayerWeapon* Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

				if (Weapon)
				{
					this->m_Data[EntityIndex].ShotsFired = Weapon->m_iShotsFired;

					if ((this->m_Data[EntityIndex].ShotsFired > 0) && (this->m_Data[EntityIndex].OldShotsFired > this->m_Data[EntityIndex].ShotsFired))
					{
						this->m_Data[EntityIndex].DecreaseShotsFired = Weapon->m_flDecreaseShotsFired;

						if (this->m_Data[EntityIndex].DecreaseShotsFired > this->m_Data[EntityIndex].OldDecreaseShotsFired)
						{
							this->m_Data[EntityIndex].GameTime = gpGlobals->time;

							if (this->m_Data[EntityIndex].DecreaseShotsFired > this->m_Data[EntityIndex].GameTime)
							{
								this->m_Data[EntityIndex].Delay = (this->m_Data[EntityIndex].DecreaseShotsFired - this->m_Data[EntityIndex].GameTime);

								if (this->m_Data[EntityIndex].DecreaseShotsFired < this->m_Data[EntityIndex].GameTime)
								{
									this->m_Data[EntityIndex].DecreaseCount = ceil(((this->m_Data[EntityIndex].GameTime - this->m_Data[EntityIndex].DecreaseShotsFired) / this->m_Data[EntityIndex].Delay));

									if (this->m_Data[EntityIndex].DecreaseCount > this->m_Data[EntityIndex].ShotsFired)
									{
										this->m_Data[EntityIndex].DecreaseCount = this->m_Data[EntityIndex].ShotsFired;
									}

									Weapon->m_flDecreaseShotsFired = (this->m_Data[EntityIndex].DecreaseShotsFired + ((float)(this->m_Data[EntityIndex].DecreaseCount) * this->m_Data[EntityIndex].Delay));

									Weapon->m_iShotsFired = (this->m_Data[EntityIndex].ShotsFired - this->m_Data[EntityIndex].DecreaseCount);
								}
								else
								{
									Weapon->m_flDecreaseShotsFired = this->m_Data[EntityIndex].DecreaseShotsFired;
								}
							}
						}
					}
				}
			}
		}
	}
}