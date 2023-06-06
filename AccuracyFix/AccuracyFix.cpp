#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	//
	this->m_AF_PunchControl_All = this->CvarRegister("af_punch_weapon_all", "-1.0");
	//
	//
	for (int WeaponID = WEAPON_P228; WeaponID <= WEAPON_P90; WeaponID++)
	{
		auto SlotInfo = g_ReGameApi->GetWeaponSlot((WeaponIdType)WeaponID);

		if (SlotInfo)
		{
			if (SlotInfo->slot == PRIMARY_WEAPON_SLOT || SlotInfo->slot == PISTOL_SLOT)
			{
				if (SlotInfo->weaponName)
				{
					char cvarName[64] = { 0 };

					Q_snprintf(cvarName, sizeof(cvarName), "af_punch_%s", SlotInfo->weaponName);

					this->m_AF_PunchControl[WeaponID] = this->CvarRegister(cvarName, "1.0");
				}
			}
		}
	}
}

cvar_t* CAccuracyFix::CvarRegister(const char* Name, const char* Value)
{
	// Get cvar pointer
	cvar_t* Pointer = g_engfuncs.pfnCVarGetPointer(Name);

	// If not exists
	if (!Pointer)
	{
		// Variable for Cvar Helper
		this->m_Cvar[Name].name = Name;

		// Set name
		this->m_Cvar[Name].string = (char*)(Value);

		// Set flags
		this->m_Cvar[Name].flags = (FCVAR_PROTECTED | FCVAR_SPONLY);

		// Register the variable
		g_engfuncs.pfnCVarRegister(&this->m_Cvar[Name]);

		// Get created pointer
		Pointer = g_engfuncs.pfnCVarGetPointer(this->m_Cvar[Name].name);

		// If is not null
		if (Pointer)
		{
			// We can set values
			g_engfuncs.pfnCvar_DirectSet(Pointer, Value);
		}
	}

	return Pointer;
}