#include "precompiled.h"

// ENGINE POST Functions Table
enginefuncs_t gENGINE_FunctionTable_Pre;

// ENGINE POST Functions Table
enginefuncs_t gENGINE_FunctionTable_Post;

#pragma region ENGINE_PRE
C_DLLEXPORT int GetEngineFunctions(enginefuncs_t* pengfuncsFromEngine, int* interfaceVersion)
{
	memset(&gENGINE_FunctionTable_Pre, 0, sizeof(enginefuncs_t));

	// Register Functions Here //

	memcpy(pengfuncsFromEngine, &gENGINE_FunctionTable_Pre, sizeof(enginefuncs_t));

	return 1;
}
#pragma endregion

#pragma region ENGINE_POST
C_DLLEXPORT int GetEngineFunctions_Post(enginefuncs_t* pengfuncsFromEngine, int* interfaceVersion)
{
	memset(&gENGINE_FunctionTable_Post, 0, sizeof(enginefuncs_t));

	gENGINE_FunctionTable_Post.pfnTraceLine = ENGINE_POST_TraceLine;

	memcpy(pengfuncsFromEngine, &gENGINE_FunctionTable_Post, sizeof(enginefuncs_t));

	return 1;
}

void ENGINE_POST_TraceLine(const float* v1, const float* v2, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	gAccuracyFix.TraceLine(v1, v2, fNoMonsters, pentToSkip, ptr);

	RETURN_META(MRES_IGNORED);
}
#pragma endregion
