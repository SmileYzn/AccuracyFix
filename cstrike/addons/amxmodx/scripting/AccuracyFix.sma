#include <amxmodx>
#include <fakemeta>

// Max Weapons
#define MAX_WEAPONS 32

// Weapon Slots by index
new const g_iWeaponSlot[MAX_WEAPONS+1] = {0, 2, 0, 1, 4, 1, 5, 1, 1, 4, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 4, 2, 1, 1, 3, 1, 0, 0};

// Player Weapon Index
new g_iPlayerWeaponId[MAX_PLAYERS+1] = {0, ...};

// Weapon accuracy value
new g_iAccuracyWeapon[MAX_WEAPONS+1] = {8192, ...};

public plugin_init()
{
	register_plugin("Accuracy Fix", "0.0.6", "SmileY", "https://github.com/smileyzn/accuracyfix", "Accuracy Fix (AMXX Plugin)");

	new szWeapon[MAX_NAME_LENGTH];
	
	for (new iWeaponId = 0; iWeaponId < MAX_WEAPONS; iWeaponId++)
	{
		if (1 <= g_iWeaponSlot[iWeaponId] <= 2)
		{
			get_weaponname(iWeaponId, szWeapon, charsmax(szWeapon));
			
			format(szWeapon, charsmax(szWeapon), "af_distance_%s", szWeapon);
			
			bind_pcvar_num(create_cvar(szWeapon, "8192", FCVAR_NONE, "", true, 0.0, true, 8192.0), g_iAccuracyWeapon[iWeaponId]);
		}
	}
	
	register_event("CurWeapon", "EV_CurWeapon", "be", "1=1");

	register_forward(FM_TraceLine, "FW_FM_TraceLine", true);
}

public EV_CurWeapon(id)
{
	g_iPlayerWeaponId[id] = get_user_weapon(id);
	
	return PLUGIN_CONTINUE;
}

public FW_FM_TraceLine(Float:vStart[3], Float:vEnd[3], iSkipMonsters, iEntity, iResult)
{
	if (iEntity > 0 && iEntity <= MaxClients)
	{
		if (pev_valid(iEntity))
		{
			if (pev(iEntity, pev_flags) & FL_CLIENT|FL_ONGROUND|FL_FAKECLIENT)
			{
				if (1 <= g_iWeaponSlot[g_iPlayerWeaponId[iEntity]] <= 2)
				{
					if (g_iAccuracyWeapon[g_iPlayerWeaponId[iEntity]] > 0)
					{
						new iTarget, iBody;
						
						new Float:Distance = get_user_aiming(iEntity, iTarget, iBody, g_iAccuracyWeapon[g_iPlayerWeaponId[iEntity]]);
						
						if (iTarget > 0 && iTarget <= MaxClients)
						{
							if (pev_valid(iTarget))
							{
								if (pev(iTarget, pev_flags) & FL_CLIENT|FL_FAKECLIENT)
								{
									new Float:vAngle[3];
								
									pev(iEntity, pev_angles, vAngle);
									
									engfunc(EngFunc_MakeVectors, vAngle);
								
									new Float:vForward[3];
								
									global_get(glb_v_forward, vForward); 
									
									new Float:vEndResult[3];
									
									vEndResult[0] = vStart[0] + vForward[0] * Distance;
									vEndResult[1] = vStart[1] + vForward[1] * Distance;
									vEndResult[2] = vStart[2] + vForward[2] * Distance;
									
									engfunc(EngFunc_TraceLine, vStart, vEndResult, iSkipMonsters, iEntity, iResult);
								}
							}
						}
					}
				}
			}
		}
	}

	return FMRES_IGNORED;
}
