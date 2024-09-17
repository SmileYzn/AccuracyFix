#pragma once

class CAccuracyUtil
{
public:
	cvar_t* CvarRegister(const char* Name, const char* Value);
	void ServerCommand(const char* Format, ...);
	const char* GetPath();
	TraceResult GetUserAiming(edict_t* pEntity, float DistanceLimit);
	
	std::string m_Path;
};

extern CAccuracyUtil gAccuracyUtil;
