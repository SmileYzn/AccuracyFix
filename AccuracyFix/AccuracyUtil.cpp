#include "precompiled.h"

CAccuracyUtil gAccuracyUtil;

cvar_t* CAccuracyUtil::CvarRegister(const char* Name, const char* Value)
{
	cvar_t* pCvar = g_engfuncs.pfnCVarGetPointer(Name);

	if (pCvar != nullptr)
		return pCvar;

	this->m_CvarData[Name].name = Name;

	this->m_CvarData[Name].string = (char*)(Value);

	this->m_CvarData[Name].flags = (FCVAR_SERVER | FCVAR_SPONLY | FCVAR_UNLOGGED);

	g_engfuncs.pfnCVarRegister(&this->m_CvarData[Name]);

	pCvar = g_engfuncs.pfnCVarGetPointer(this->m_CvarData[Name].name);

	if (pCvar != nullptr)
	{
		g_engfuncs.pfnCvar_DirectSet(pCvar, Value);
	}

	return pCvar;
}

const char* CAccuracyUtil::GetPath()
{
	if (!this->m_Path.empty())
		return this->m_Path.c_str();

	std::string GameDir = gpMetaUtilFuncs->pfnGetGameInfo(&Plugin_info, GINFO_GAMEDIR);

	if (GameDir.empty())
		return this->m_Path.c_str();
	this->m_Path = gpMetaUtilFuncs->pfnGetPluginPath(&Plugin_info);

	if (this->m_Path.empty())
		return this->m_Path.c_str();

	this->m_Path.erase(0, GameDir.length() + 1U);

	std::replace(this->m_Path.begin(), this->m_Path.end(), (char)(92), (char)(47));

	auto SlashPos = this->m_Path.find_last_of((char)(47));

	if (SlashPos != std::string::npos)
		this->m_Path.erase(SlashPos, this->m_Path.length());

	while (std::count(this->m_Path.begin(), this->m_Path.end(), (char)(47)) > 1)
	{
		SlashPos = this->m_Path.find_last_of((char)(47));

		if (SlashPos == std::string::npos)
			continue;
		
		this->m_Path.erase(SlashPos, this->m_Path.length());
	}

	return this->m_Path.c_str();
}


void CAccuracyUtil::ServerCommand(const char* Format, ...)
{
	char Command[255] = { 0 };

	va_list	argptr;

	va_start(argptr, Format);

	vsnprintf(Command, sizeof(Command), Format, argptr);

	va_end(argptr);

	Q_strncat(Command, "\n", 1);

	g_engfuncs.pfnServerCommand(Command);
}

TraceResult CAccuracyUtil::GetUserAiming(edict_t* pEntity, float DistanceLimit)
{
	TraceResult Result = { };

	if (FNullEnt(pEntity))
		return Result;

	auto EntityIndex = g_engfuncs.pfnIndexOfEdict(pEntity);

	if (EntityIndex > 0 && EntityIndex <= gpGlobals->maxClients)
	{
		Vector v_forward;

		Vector v_src = pEntity->v.origin + pEntity->v.view_ofs;

		g_engfuncs.pfnAngleVectors(pEntity->v.v_angle, v_forward, NULL, NULL);

		Vector v_dest = v_src + v_forward * DistanceLimit;

		g_engfuncs.pfnTraceLine(v_src, v_dest, 0, pEntity, &Result);
	}

	return Result;
}
