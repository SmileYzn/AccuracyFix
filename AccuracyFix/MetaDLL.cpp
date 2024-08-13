#include "precompiled.h"

// DLL PRE Functions Table
DLL_FUNCTIONS gDLL_FunctionTable_Pre;

// DLL POST Functions Table
DLL_FUNCTIONS gDLL_FunctionTable_Post;

#pragma region DLL_PRE
C_DLLEXPORT int GetEntityAPI2(DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion)
{
	memset(&gDLL_FunctionTable_Pre, 0, sizeof(DLL_FUNCTIONS));

	// Register Functions Here //

	memcpy(pFunctionTable, &gDLL_FunctionTable_Pre, sizeof(DLL_FUNCTIONS));

	return 1;
}
#pragma endregion

#pragma region DLL_POST
C_DLLEXPORT int GetEntityAPI2_Post(DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion)
{
	memset(&gDLL_FunctionTable_Post, 0, sizeof(DLL_FUNCTIONS));

	// Register Functions Here //
	gDLL_FunctionTable_Post.pfnServerActivate = DLL_POST_ServerActivate;
	memcpy(pFunctionTable, &gDLL_FunctionTable_Post, sizeof(DLL_FUNCTIONS));

	return 1;
}

void DLL_POST_ServerActivate(edict_t* pEdictList, int edictCount, int clientMax)
{
	gAccuracyFix.ServerActivate();

	RETURN_META(MRES_IGNORED);
}
#pragma endregion
