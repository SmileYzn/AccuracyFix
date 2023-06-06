#pragma once

class CAccuracyFix
{
public:
	void ServerActivate();

	cvar_t* CvarRegister(const char* Name, const char* Value);
public:
	// Punch Angle Control
	cvar_t* m_AF_PunchControl_All;
	cvar_t* m_AF_PunchControl[MAX_WEAPONS + 1];
	
	// Static data
	std::map<std::string, cvar_t> m_Cvar;
};

extern CAccuracyFix gAccuracyFix;