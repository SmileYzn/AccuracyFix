#pragma once

#pragma region DLL_PRE
#pragma endregion

#pragma region DLL_POST
void DLL_POST_ServerActivate(edict_t* pEdictList, int edictCount, int clientMax);
#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
void DLL_POST_CmdEnd(const edict_t* pEdict);
#endif
#pragma endregion