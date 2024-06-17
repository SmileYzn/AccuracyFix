/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#pragma once

const int MAX_SENTENCE_NAME      = 16;
const int MAX_SENTENCE_VOXFILE   = 1536;	// max number of sentences in game. NOTE: this must match CVOXFILESENTENCEMAX in engine\sound.h

const int MAX_SENTENCE_GROUPS    = 200;		// max number of sentence groups
const int MAX_SENTENCE_LRU       = 32;		// max number of elements per sentence group
const int MAX_SENTENCE_DPV_RESET = 27;		// max number of dynamic pitch volumes

const float MAX_ANNOUNCE_MINS    = 2.25f;
const float MIN_ANNOUNCE_MINS    = 0.25f;

enum LowFreqOsc : int
{
	LFO_OFF = 0,
	LFO_SQUARE,		// square
	LFO_TRIANGLE,	// triangle
	LFO_RANDOM,		// random
};

// group of related sentences
struct sentenceg
{
	char szgroupname[16];
	int count;
	unsigned char rgblru[MAX_SENTENCE_LRU];
};

// runtime pitch shift and volume fadein/out structure

// NOTE: IF YOU CHANGE THIS STRUCT YOU MUST CHANGE THE SAVE/RESTORE VERSION NUMBER
// SEE BELOW (in the typedescription for the class)
typedef struct dynpitchvol
{
	// NOTE: do not change the order of these parameters
	// NOTE: unless you also change order of rgdpvpreset array elements!
	int preset;

	int pitchrun;		// pitch shift % when sound is running 0 - 255
	int pitchstart;		// pitch shift % when sound stops or starts 0 - 255
	int spinup;			// spinup time 0 - 100
	int spindown;		// spindown time 0 - 100

	int volrun;			// volume change % when sound is running 0 - 10
	int volstart;		// volume change % when sound stops or starts 0 - 10
	int fadein;			// volume fade in time 0 - 100
	int fadeout;		// volume fade out time 0 - 100

	// Low Frequency Oscillator
	LowFreqOsc lfotype;	// 0) off 1) square 2) triangle 3) random
	int lforate;		// 0 - 1000, how fast lfo osciallates

	int lfomodpitch;	// 0-100 mod of current pitch. 0 is off.
	int lfomodvol;		// 0-100 mod of current volume. 0 is off.

	int cspinup;		// each trigger hit increments counter and spinup pitch

	int cspincount;
	int pitch;
	int spinupsav;
	int spindownsav;
	int pitchfrac;
	int vol;
	int fadeinsav;
	int fadeoutsav;
	int volfrac;
	int lfofrac;
	int lfomult;

} dynpitchvol_t;

#define SF_AMBIENT_SOUND_STATIC         0 // medium radius attenuation
#define SF_AMBIENT_SOUND_EVERYWHERE     0x0001
#define SF_AMBIENT_SOUND_SMALLRADIUS    0x0002
#define SF_AMBIENT_SOUND_MEDIUMRADIUS   0x0004
#define SF_AMBIENT_SOUND_LARGERADIUS    0x0008
#define SF_AMBIENT_SOUND_START_SILENT   0x0016
#define SF_AMBIENT_SOUND_NOT_LOOPING    0x0032

class CAmbientGeneric: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
public:
	float m_flAttenuation;	// attenuation value
	dynpitchvol_t m_dpv;
	BOOL m_fActive;			// only TRUE when the entity is playing a looping sound
	BOOL m_fLooping;		// TRUE when the sound played will loop
};

class CEnvSound: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
public:
	float m_flRadius;
	float m_flRoomtype;
};

#define SF_SPEAKER_START_SILENT	0x0001 // wait for trigger 'on' to start announcements

class CSpeaker: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
public:
	int m_preset;		// preset number
};
