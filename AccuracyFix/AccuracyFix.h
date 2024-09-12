#pragma once

/**
* global_get(glb_trace_flags) values
* @note Custom flags that we can retrieve in pfnShouldCollide/TraceLine/TraceHull
*/
#define FTRACE_BULLET                   (1<<16)
#define FTRACE_FLASH                    (1<<17)
#define FTRACE_KNIFE                    (1<<18)

class CAccuracyFix
{
public:
	void ServerActivate();
	void TraceLine(const float* vStart, const float* vEnd, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);

private:
	cvar_t* m_af_distance_all;
	cvar_t* m_af_distance[MAX_WEAPONS + 1];
	cvar_t* m_af_accuracy_all;
	cvar_t* m_af_accuracy[MAX_WEAPONS + 1];
	cvar_t* m_af_jump_fix;
};

extern CAccuracyFix gAccuracyFix;
