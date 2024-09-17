#include "precompiled.h"

CAccuracyUtil gAccuracyUtil;

cvar_t* CAccuracyUtil::CvarRegister(const char* Name, const char* Value)
{
	cvar_t* Pointer = g_engfuncs.pfnCVarGetPointer(Name);

	if (!Pointer)
	{
		static cvar_t CvarData;
		
		CvarData = { Name, (char*)(Value), FCVAR_SERVER | FCVAR_SPONLY, 0.0f, NULL };

		g_engfuncs.pfnCVarRegister(&CvarData);
		
		Pointer = g_engfuncs.pfnCVarGetPointer(Name);

		if(Pointer)
		{
			g_engfuncs.pfnCvar_DirectSet(Pointer, Value);
		}
	}

	return Pointer;
}


const char* CAccuracyUtil::GetPath()
{
	if (this->m_Path.empty())
	{
		std::string GameDir = gpMetaUtilFuncs->pfnGetGameInfo(&Plugin_info, GINFO_GAMEDIR);

		if (!GameDir.empty())
		{
			this->m_Path = gpMetaUtilFuncs->pfnGetPluginPath(&Plugin_info);

			if (!this->m_Path.empty())
			{
				this->m_Path.erase(0, GameDir.length() + 1U);

				std::replace(this->m_Path.begin(), this->m_Path.end(), (char)(92), (char)(47));

				this->m_Path.erase(this->m_Path.find_last_of((char)(47)), this->m_Path.length());

				while (std::count(this->m_Path.begin(), this->m_Path.end(), (char)(47)) > 1)
				{
					this->m_Path.erase(this->m_Path.find_last_of((char)(47)), this->m_Path.length());
				}
			}
		}
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

	Q_strncat(Command, "\n", sizeof(Command) - 1);

	g_engfuncs.pfnServerCommand(Command);
}

TraceResult CAccuracyUtil::GetUserAiming(edict_t* pEntity, float DistanceLimit)
{
	TraceResult Result = { };

	if (!FNullEnt(pEntity))
	{
		auto EntityIndex = g_engfuncs.pfnIndexOfEdict(pEntity);

		if (EntityIndex > 0 && EntityIndex <= gpGlobals->maxClients)
		{
			Vector v_forward;

			Vector v_src = pEntity->v.origin + pEntity->v.view_ofs;

			g_engfuncs.pfnAngleVectors(pEntity->v.v_angle, v_forward, NULL, NULL);

			Vector v_dest = v_src + v_forward * DistanceLimit;
			
			g_engfuncs.pfnTraceLine(v_src, v_dest, 0, pEntity, &Result);
		}
	}

	return Result;
}
