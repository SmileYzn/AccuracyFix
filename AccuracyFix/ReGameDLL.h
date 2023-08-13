#pragma once

extern IReGameApi			*g_ReGameApi;
extern const ReGameFuncs_t	*g_ReGameFuncs;
extern IReGameHookchains	*g_ReGameHookchains;
extern CGameRules			*g_pGameRules;

extern bool ReGameDLL_Init();
extern bool ReGameDLL_Stop();

CGameRules *ReGameDLL_InstallGameRules(IReGameHook_InstallGameRules* chain);
#ifndef ACCURACY_DISABLE_RECOIL_CONTROL
void ReGameDLL_CBasePlayer_PostThink(IReGameHook_CBasePlayer_PostThink* chain, CBasePlayer* pthis);
#endif