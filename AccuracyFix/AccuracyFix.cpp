#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	this->m_af_accuracy_all = gAccuracyUtil.CvarRegister("af_accuracy_all", "-1.0");

	this->m_af_distance_all = gAccuracyUtil.CvarRegister("af_distance_all", "-1.0");

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
	this->m_Data.clear();

	this->m_af_recoil_all = gAccuracyUtil.CvarRegister("af_recoil_all", "-1.0");
#endif

	for (int WeaponID = WEAPON_P228; WeaponID <= WEAPON_P90; WeaponID++)
	{
		auto SlotInfo = g_ReGameApi->GetWeaponSlot((WeaponIdType)WeaponID);

		if (!SlotInfo)
			continue;

		if (!((SlotInfo->slot == PRIMARY_WEAPON_SLOT) || (SlotInfo->slot == PISTOL_SLOT)))
			continue;

		if (!SlotInfo->weaponName || SlotInfo->weaponName[0u] == '\0')
			continue;

		char cvarName[64] = { 0 };

		Q_snprintf(cvarName, sizeof(cvarName), "af_distance_%s", SlotInfo->weaponName);

		this->m_af_distance[WeaponID] = gAccuracyUtil.CvarRegister(cvarName, "8192.0");

		Q_snprintf(cvarName, sizeof(cvarName), "af_accuracy_%s", SlotInfo->weaponName);

		this->m_af_accuracy[WeaponID] = gAccuracyUtil.CvarRegister(cvarName, "9999.0");

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
		Q_snprintf(cvarName, sizeof(cvarName), "af_recoil_%s", SlotInfo->weaponName);

		this->m_af_recoil[WeaponID] = gAccuracyUtil.CvarRegister(cvarName, "1.0");
#endif
	}

	auto Path = gAccuracyUtil.GetPath();

	if (!Path || Path[0u] == '\0')
		return;

	gAccuracyUtil.ServerCommand("exec %s/accuracyfix.cfg", Path);
}

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
void CAccuracyFix::CmdEnd(const edict_t* pEdict)
{
	auto Player = UTIL_PlayerByIndexSafe(ENTINDEX(pEdict));

	if (!Player)
		return;

	if (!Player->IsAlive())
		return;

	this->m_Data[Player->entindex()].LastFired = Player->m_flLastFired;
}
#endif

void CAccuracyFix::TraceLine(const float* vStart, const float* vEnd, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	if (fNoMonsters != dont_ignore_monsters || FNullEnt(pentToSkip))
		return;

	auto EntityIndex = g_engfuncs.pfnIndexOfEdict(pentToSkip);

	if (!(EntityIndex > 0 && EntityIndex <= gpGlobals->maxClients))
		return;

	auto Player = UTIL_PlayerByIndexSafe(EntityIndex);

	if (!Player || !Player->IsAlive() || !Player->m_pActiveItem || 
		!((Player->m_pActiveItem->iItemSlot() == PRIMARY_WEAPON_SLOT) || (Player->m_pActiveItem->iItemSlot() == PISTOL_SLOT)))
	{
		return;
	}

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
	if (!((Player->edict()->v.button & IN_ATTACK) && (Player->m_flLastFired = this->m_Data[EntityIndex].LastFired)))
		return;

	this->m_Data[EntityIndex].LastFired = Player->m_flLastFired;

	this->m_Data[EntityIndex].WeaponId = Player->m_pActiveItem->m_iId;
#endif
	auto DistanceLimit = this->m_af_distance[Player->m_pActiveItem->m_iId]->value;

	if (this->m_af_distance_all->value > 0)
	{
		DistanceLimit = this->m_af_distance_all->value;
	}

	if (!(DistanceLimit > 0.0f && Player->edict()->v.flags & FL_ONGROUND))
		return;

	auto trResult = gAccuracyUtil.GetUserAiming(pentToSkip, DistanceLimit);

	if (!(trResult.flFraction != 1.0f && !FNullEnt(trResult.pHit)))
		return;

	auto TargetIndex = ENTINDEX(trResult.pHit);

	if (!(TargetIndex > 0 && TargetIndex <= gpGlobals->maxClients))
		return;

	auto fwdVelocity = this->m_af_accuracy[Player->m_pActiveItem->m_iId]->value;

	if (this->m_af_accuracy_all->value > 0.0f)
	{
		fwdVelocity = this->m_af_accuracy_all->value;
	}

	g_engfuncs.pfnMakeVectors(pentToSkip->v.v_angle);

	auto vEndRes = (Vector)vStart + gpGlobals->v_forward * fwdVelocity;

	g_engfuncs.pfnTraceLine(vStart, vEndRes, fNoMonsters, pentToSkip, ptr);
}

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
void CAccuracyFix::PostThink(CBasePlayer* Player)
{
	if (!Player->IsAlive())
		return;
	auto EntityIndex = Player->entindex();

	if (this->m_Data[EntityIndex].WeaponId == WEAPON_NONE)
		return;
	
	auto Recoil = this->m_af_recoil[this->m_Data[EntityIndex].WeaponId]->value;

	if (Recoil > 0.0f)
	{
		if (this->m_af_recoil_all->value > 0.0f)
		{
			Recoil = this->m_af_recoil_all->value;
		}

		auto PunchAngle = Player->edict()->v.punchangle;

		PunchAngle = PunchAngle * Recoil;

		Player->edict()->v.punchangle = PunchAngle;
	}

	this->m_Data[EntityIndex].WeaponId = WEAPON_NONE;
}
#endif
