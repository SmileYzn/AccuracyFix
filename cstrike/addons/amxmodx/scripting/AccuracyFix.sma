#include <amxmodx>
#include <fakemeta>

#define MAX_WEAPONS 32

enum _:WeaponInfo
{
	Index,
	Name[MAX_NAME_LENGTH],
	Slot
};

new g_hRegUserMsg;

new g_eServerWeaponInfo[MAX_WEAPONS+1][WeaponInfo];
new g_ePlayerWeaponInfo[MAX_PLAYERS+1][WeaponInfo];

new g_iAccuracyAim[MAX_WEAPONS+1] = {8192, ...};

public plugin_init()
{
	register_plugin("Accuracy Fix", "0.0.5", "SmileY", "https://github.com/smileyzn/accuracyfix", "Accuracy Fix (AMXX Plugin)");

	for (new i = 0; i < MAX_WEAPONS;i++)
	{
		if (g_eServerWeaponInfo[i][Index])
		{
			bind_pcvar_num(create_cvar(fmt("af_distance_%s", g_eServerWeaponInfo[i][Name]),"8192", FCVAR_NONE, "", true, 0.0, true, 8192.0), g_iAccuracyAim[i]);
		}
	}
	
	register_event("CurWeapon", "EV_CurWeapon", "be", "1=1");

	register_forward(FM_TraceLine, "FW_FM_TraceLine", true);
}

public plugin_precache()
{
	g_hRegUserMsg = register_forward(FM_RegUserMsg,"FW_FM_RegUserMsg", true);
}

public FW_FM_RegUserMsg(szMsg[], iSize)
{
	if (equali(szMsg, "WeaponList"))
	{
		register_message(get_orig_retval(), "MSG_WeaponList");
		
		unregister_forward(FM_RegUserMsg, g_hRegUserMsg, true);
	}
}

public MSG_WeaponList(iMsgId, iMsgDest, iMsgEntity)
{
	new iWeaponId = get_msg_arg_int(8);
	
	if (iWeaponId)
	{
		new iSlot = get_msg_arg_int(6);
		
		if (0 <= iSlot <= 1)
		{
			g_eServerWeaponInfo[iWeaponId][Index] = iWeaponId;
			
			g_eServerWeaponInfo[iWeaponId][Slot] = iSlot;
			
			get_msg_arg_string(1, g_eServerWeaponInfo[iWeaponId][Name], 32);			
		}
	}
	
	return PLUGIN_CONTINUE;
}

public EV_CurWeapon(id)
{
	new iWeaponId = get_user_weapon(id);
	
	if (iWeaponId)
	{
		g_ePlayerWeaponInfo[id] = g_eServerWeaponInfo[iWeaponId];
	}
	
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
				if (0 <= g_ePlayerWeaponInfo[iEntity][Slot] <= 1)
				{
					if (g_iAccuracyAim[g_ePlayerWeaponInfo[iEntity][Index]] > 0)
					{
						new iTarget, iBody;

						new Float:Distance = get_user_aiming(iEntity, iTarget, iBody, g_iAccuracyAim[g_ePlayerWeaponInfo[iEntity][Index]]);

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
