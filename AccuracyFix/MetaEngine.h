#pragma once

#pragma region ENGINE_PRE
#pragma endregion

#pragma region ENGINE_POST
void ENGINE_POST_TraceLine(const float* v1, const float* v2, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
#pragma endregion