/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#pragma once

#include "util.h"
#include "schedule.h"
#include "saverestore.h"
#include "scriptevent.h"
#include "monsterevent.h"

class CSave;
class CRestore;
class CBasePlayer;
class CBaseEntity;
class CBaseMonster;
class CBasePlayerItem;
class CSquadMonster;
class CCSEntity;

#define SetThink(a)\
	m_pfnThink = static_cast<void (CBaseEntity::*)()>(a)
#define SetTouch(a)\
	m_pfnTouch = static_cast<void (CBaseEntity::*)(CBaseEntity *)>(a)
#define SetUse(a)\
	m_pfnUse = static_cast<void (CBaseEntity::*)(CBaseEntity *, CBaseEntity *, USE_TYPE, float)>(a)
#define SetBlocked(a)\
	m_pfnBlocked = static_cast<void (CBaseEntity::*)(CBaseEntity *)>(a)

#define SetMoveDone(a)\
	m_pfnCallWhenMoveDone = static_cast<void (CBaseToggle::*)()>(a)

class CBaseEntity {
public:
	// Constructor. Set engine to use C/C++ callback functions
	// pointers to engine data
	entvars_t *pev;					// Don't need to save/restore this pointer, the engine resets it

	// path corners
	CBaseEntity *m_pGoalEnt;		// path corner we are heading towards
	CBaseEntity *m_pLink;			// used for temporary link-list operations.

	// initialization functions
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Activate() = 0;

	// Setup the object->object collision box (pev->mins / pev->maxs is the object->world collision box)
	virtual void SetObjectCollisionBox() = 0;

	// Classify - returns the type of group (i.e, "houndeye", or "human military" so that monsters with different classnames
	// still realize that they are teammates. (overridden for monsters that form groups)
	virtual int Classify() = 0;
	virtual void DeathNotice(entvars_t *pevChild) = 0;

	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual BOOL TakeHealth(float flHealth, int bitsDamageType) = 0;
	virtual void Killed(entvars_t *pevAttacker, int iGib) = 0;
	virtual int BloodColor() = 0;
	virtual void TraceBleed(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) = 0;
	virtual BOOL IsTriggered(CBaseEntity *pActivator) = 0;
	virtual CBaseMonster *MyMonsterPointer() = 0;
	virtual CSquadMonster *MySquadMonsterPointer() = 0;
	virtual int GetToggleState() = 0;
	virtual void AddPoints(int score, BOOL bAllowNegativeScore) = 0;
	virtual void AddPointsToTeam(int score, BOOL bAllowNegativeScore) = 0;
	virtual BOOL AddPlayerItem(CBasePlayerItem *pItem) = 0;
	virtual BOOL RemovePlayerItem(CBasePlayerItem *pItem) = 0;
	virtual int GiveAmmo(int iAmount, const char *szName, int iMax = -1) = 0;
	virtual float GetDelay() = 0;
	virtual int IsMoving() = 0;
	virtual void OverrideReset() = 0;
	virtual int DamageDecal(int bitsDamageType) = 0;

	// This is ONLY used by the node graph to test movement through a door
	virtual void SetToggleState(int state) = 0;
	virtual void StartSneaking() = 0;
	virtual void UpdateOnRemove() = 0;
	virtual BOOL OnControls(entvars_t *onpev) = 0;
	virtual BOOL IsSneaking() = 0;
	virtual BOOL IsAlive() = 0;
	virtual BOOL IsBSPModel() = 0;
	virtual BOOL ReflectGauss() = 0;
	virtual BOOL HasTarget(string_t targetname) = 0;
	virtual BOOL IsInWorld() = 0;
	virtual BOOL IsPlayer() = 0;
	virtual BOOL IsNetClient() = 0;
	virtual const char *TeamID() = 0;

	virtual CBaseEntity *GetNextTarget() = 0;

	// fundamental callbacks
	void (CBaseEntity::*m_pfnThink)();
	void (CBaseEntity::*m_pfnTouch)(CBaseEntity *pOther);
	void (CBaseEntity::*m_pfnUse)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void (CBaseEntity::*m_pfnBlocked)(CBaseEntity *pOther);

	virtual void Think() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType = USE_OFF, float value = 0.0f) = 0;
	virtual void Blocked(CBaseEntity *pOther) = 0;

	virtual CBaseEntity *Respawn() = 0;
	virtual void UpdateOwner() = 0;
	virtual BOOL FBecomeProne() = 0;

	virtual Vector Center() = 0;								// center point of entity
	virtual Vector EyePosition() = 0;							// position of eyes
	virtual Vector EarPosition() = 0;							// position of ears
	virtual Vector BodyTarget(const Vector &posSrc) = 0;		// position to shoot at

	virtual int Illumination() = 0;
	virtual BOOL FVisible(CBaseEntity *pEntity) = 0;
	virtual BOOL FVisible(const Vector &vecOrigin) = 0;
public:
	static CBaseEntity *Instance(edict_t *pent) { return (CBaseEntity *)GET_PRIVATE(pent ? pent : ENT(0)); }
	static CBaseEntity *Instance(entvars_t *pev) { return Instance(ENT(pev)); }
	static CBaseEntity *Instance(int offset) { return Instance(ENT(offset)); }

	edict_t *edict();
	EOFFSET eoffset();
	int entindex();
	int IsDormant();

	bool Intersects(CBaseEntity *pOther);
	bool Intersects(const Vector &mins, const Vector &maxs);

	// Exports func's, useful method's for SetThink
	void EXPORT SUB_CallUseToggle();
	{
		Use(this, this, USE_TOGGLE, 0);
	}

	void EXPORT SUB_Remove()
	{
		if (pev->health > 0)
		{
			// this situation can screw up monsters who can't tell their entity pointers are invalid.
			pev->health = 0;
			ALERT(at_aiconsole, "SUB_Remove called on entity with health > 0\n");
		}

		REMOVE_ENTITY(ENT(pev));
	}

public:
	// NOTE: it was replaced on member "int *current_ammo" because it is useless.
	CCSEntity *m_pEntity;

	// We use this variables to store each ammo count.
	float currentammo;
	int maxammo_buckshot;
	int ammo_buckshot;
	int maxammo_9mm;
	int ammo_9mm;
	int maxammo_556nato;
	int ammo_556nato;
	int maxammo_556natobox;
	int ammo_556natobox;
	int maxammo_762nato;
	int ammo_762nato;
	int maxammo_45acp;
	int ammo_45acp;
	int maxammo_50ae;
	int ammo_50ae;
	int maxammo_338mag;
	int ammo_338mag;
	int maxammo_57mm;
	int ammo_57mm;
	int maxammo_357sig;
	int ammo_357sig;

	// Special stuff for grenades and knife.
	float m_flStartThrow;
	float m_flReleaseThrow;
	int m_iSwing;

	// client has left the game
	bool has_disconnected;
};

// Inlines
inline BOOL FNullEnt(CBaseEntity *ent) { return (ent == NULL || FNullEnt(ent->edict())); }

class CPointEntity: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
};

// generic Delay entity
class CBaseDelay: public CBaseEntity {
public:
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
public:
	float m_flDelay;
	string_t m_iszKillTarget;
};

class CBaseAnimating: public CBaseDelay {
public:
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void HandleAnimEvent(MonsterEvent_t *pEvent) = 0;
public:
	// animation needs
	float m_flFrameRate;		// computed FPS for current sequence
	float m_flGroundSpeed;		// computed linear movement rate for current sequence
	float m_flLastEventCheck;	// last time the event list was checked
	BOOL m_fSequenceFinished;	// flag set when StudioAdvanceFrame moves across a frame boundry
	BOOL m_fSequenceLoops;		// true if the sequence loops
};

// EHANDLE. Safe way to point to CBaseEntities who may die between frames
class EHANDLE {
public:
	edict_t *Get();
	edict_t *Set(edict_t *pent);

	operator int();
	operator CBaseEntity*();
	operator CBasePlayer*();

	CBaseEntity *operator=(CBaseEntity *pEntity);
	CBaseEntity *operator->();

private:
	edict_t *m_pent;
	int m_serialnumber;
};

// generic Toggle entity.
class CBaseToggle: public CBaseAnimating {
public:
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int GetToggleState() = 0;
	virtual float GetDelay() = 0;
public:
	TOGGLE_STATE m_toggle_state;
	float m_flActivateFinished;	// like attack_finished, but for doors
	float m_flMoveDistance;		// how far a door should slide or rotate
	float m_flWait;
	float m_flLip;
	float m_flTWidth;			// for plats
	float m_flTLength;			// for plats

	Vector m_vecPosition1;
	Vector m_vecPosition2;
	Vector m_vecAngle1;
	Vector m_vecAngle2;

	int m_cTriggersLeft;		// trigger_counter only, # of activations remaining
	float m_flHeight;
	EHANDLE m_hActivator;
	void (CBaseToggle::*m_pfnCallWhenMoveDone)();
	Vector m_vecFinalDest;
	Vector m_vecFinalAngle;

	int m_bitsDamageInflict;	// DMG_ damage type that the door or tigger does

	string_t m_sMaster;			// If this button has a master switch, this is the targetname.
								// A master switch must be of the multisource type. If all
								// of the switches in the multisource have been triggered, then
								// the button will be allowed to operate. Otherwise, it will be
								// deactivated.
};

#include "world.h"
#include "basemonster.h"
#include "player.h"

#define SF_BUTTON_DONTMOVE      BIT(0)
#define SF_BUTTON_TOGGLE        BIT(5) // button stays pushed until reactivated
#define SF_BUTTON_SPARK_IF_OFF  BIT(6) // button sparks in OFF state
#define SF_BUTTON_TOUCH_ONLY    BIT(8) // button only fires as a result of USE key.

// Generic Button
class CBaseButton: public CBaseToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;	// Buttons that don't take damage can be IMPULSE used
public:
	BOOL m_fStayPushed;				// button stays pushed in until touched again?
	BOOL m_fRotating;				// a rotating button?  default is a sliding button.

	string_t m_strChangeTarget;		// if this field is not null, this is an index into the engine string array.
									// when this button is touched, it's target entity's TARGET field will be set
									// to the button's ChangeTarget. This allows you to make a func_train switch paths, etc.

	locksound_t m_ls;				// door lock sounds

	byte m_bLockedSound;			// ordinals from entity selection
	byte m_bLockedSentence;
	byte m_bUnlockedSound;
	byte m_bUnlockedSentence;
	int m_sounds;
};

// MultiSouce
#define MAX_MS_TARGETS 32 // maximum number of targets a single multisource entity may be assigned.
#define SF_MULTI_INIT BIT(0)

class CMultiSource: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual BOOL IsTriggered(CBaseEntity *pActivator) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	EHANDLE m_rgEntities[MAX_MS_TARGETS];
	int m_rgTriggered[MAX_MS_TARGETS];

	int m_iTotal;
	string_t m_globalstate;
};

#define SF_WORLD_DARK       BIT(0) // Fade from black at startup
#define SF_WORLD_TITLE      BIT(1) // Display game title at startup
#define SF_WORLD_FORCETEAM  BIT(2) // Force teams

// This spawns first when each level begins.
class CWorld: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
};

// Converts a entvars_t * to a class pointer
// It will allocate the class and entity if necessary
template <class T>
T *GetClassPtr(T *a)
{
	entvars_t *pev = (entvars_t *)a;

	// allocate entity if necessary
	if (pev == nullptr)
		pev = VARS(CREATE_ENTITY());

	// get the private data
	a = (T *)GET_PRIVATE(ENT(pev));

	if (a == nullptr)
	{
		// allocate private data
		a = new(pev) T;
		a->pev = pev;
	}

	return a;
}

// Inlines
inline edict_t *CBaseEntity::edict()
{
	return ENT(pev);
}

inline EOFFSET CBaseEntity::eoffset()
{
	return OFFSET(pev);
}

inline int CBaseEntity::entindex()
{
	return ENTINDEX(edict());
}

inline int CBaseEntity::IsDormant()
{
	return (pev->flags & FL_DORMANT) == FL_DORMANT;
}

inline bool CBaseEntity::Intersects(CBaseEntity *pOther)
{
	return Intersects(pOther->pev->absmin, pOther->pev->absmax);
}

inline bool CBaseEntity::Intersects(const Vector &mins, const Vector &maxs)
{
	if (mins.x > pev->absmax.x
		|| mins.y > pev->absmax.y
		|| mins.z > pev->absmax.z
		|| maxs.x < pev->absmin.x
		|| maxs.y < pev->absmin.y
		|| maxs.z < pev->absmin.z)
	{
		return false;
	}

	return true;
}

inline edict_t *EHANDLE::Get()
{
	if (!m_pent || m_pent->serialnumber != m_serialnumber)
		return nullptr;

	return m_pent;
}

inline edict_t *EHANDLE::Set(edict_t *pent)
{
	m_pent = pent;
	if (pent)
		m_serialnumber = pent->serialnumber;

	return pent;
}

inline EHANDLE::operator int()
{
	return Get() != nullptr;
}

inline EHANDLE::operator CBaseEntity *()
{
	return (CBaseEntity *)GET_PRIVATE(Get());
}

inline EHANDLE::operator CBasePlayer *()
{
	return static_cast<CBasePlayer *>(GET_PRIVATE(Get()));
}

inline CBaseEntity *EHANDLE::operator=(CBaseEntity *pEntity)
{
	if (pEntity)
	{
		m_pent = ENT(pEntity->pev);
		if (m_pent)
			m_serialnumber = m_pent->serialnumber;
	}
	else
	{
		m_pent = nullptr;
		m_serialnumber = 0;
	}

	return pEntity;
}

inline CBaseEntity *EHANDLE::operator->()
{
	return (CBaseEntity *)GET_PRIVATE(Get());
}
