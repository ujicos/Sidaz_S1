#pragma once
#include "stdafx.h"
#include <vector>


typedef unsigned char byte;

typedef enum
{
	DVAR_FLAG_NONE = 0x0,				//no flags
	DVAR_FLAG_SAVED = 0x1,				//saves in config_mp.cfg for clients
	DVAR_FLAG_LATCHED = 0x2,			//no changing apart from initial value (although it might apply on a map reload, I think)
	DVAR_FLAG_CHEAT = 0x4,				//cheat
	DVAR_FLAG_REPLICATED = 0x8,			//on change, this is sent to all clients (if you are host)
	DVAR_FLAG_UNKNOWN10 = 0x10,			//unknown
	DVAR_FLAG_UNKNOWN20 = 0x20,			//unknown
	DVAR_FLAG_UNKNOWN40 = 0x40,			//unknown
	DVAR_FLAG_UNKNOWN80 = 0x80,			//unknown
	DVAR_FLAG_USERCREATED = 0x100,		//a 'set' type command created it
	DVAR_FLAG_USERINFO = 0x200,			//userinfo?
	DVAR_FLAG_SERVERINFO = 0x400,		//in the getstatus oob
	DVAR_FLAG_WRITEPROTECTED = 0x800,	//write protected
	DVAR_FLAG_UNKNOWN1000 = 0x1000,		//unknown
	DVAR_FLAG_READONLY = 0x2000,		//read only (same as 0x800?)
	DVAR_FLAG_UNKNOWN4000 = 0x4000,		//unknown
	DVAR_FLAG_UNKNOWN8000 = 0x8000,		//unknown
	DVAR_FLAG_UNKNOWN10000 = 0x10000,	//unknown
	DVAR_FLAG_DEDISAVED = 0x1000000,	//unknown
	DVAR_FLAG_NONEXISTENT = 0xFFFFFFFF	//no such dvar
} dvar_flag;

enum DvarSetSource
{
	DVAR_SOURCE_INTERNAL = 0,
	DVAR_SOURCE_EXTERNAL = 1,
	DVAR_SOURCE_SCRIPT = 2
};

union DvarLimits {
	struct
	{
		int stringCount;
		char * * strings;
	} enumeration;
	struct
	{
		int min;
		int max;
	} integer;
	struct
	{
		float min;
		float max;
	} decimal;
};

union DvarValue {
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	float value;
	float vector[4];
	char * string;
	BYTE color[4];
};

typedef enum DvarType : char
{
	DVAR_TYPE_BOOL = 0x00,
	DVAR_TYPE_FLOAT = 0x01,
	DVAR_TYPE_VEC2 = 0x02,
	DVAR_TYPE_VEC3 = 0x03,
	DVAR_TYPE_VEC4 = 0x04,
	DVAR_TYPE_INT = 0x05,
	DVAR_TYPE_ENUM = 0x06,
	DVAR_TYPE_STRING = 0x07,
	DVAR_TYPE_COLOR = 0x08,
	DVAR_TYPE_DEVTWEAK = 0x09
} DvarType;


typedef struct dvar_t //dvar struct
{
	char * name;
	dvar_flag flags;
	DvarType type;
	bool modified;

	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarLimits domain;
	dvar_t * next;
} dvar_t;


struct scr_entref_t
{
	unsigned __int16 entnum;
	unsigned __int16 classnum;
};


struct Vector3 {
	float vec[3];

	Vector3(float _x, float _y, float _z);
	Vector3(const float* origin);

	void Add(float val);
	void Add(Vector3 val);
	void Add(const float* val);

	void Subtract(float val);
	void Subtract(Vector3 val);
	void Subtract(const float* val);

	void Divide(float val);
	void Divide(Vector3 val);
	void Divide(const float* val);

	void Multiply(float val);
	void Multiply(Vector3 val);
	void Multiply(const float* val);
};


enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0x0,
	TRACE_HITTYPE_ENTITY = 0x1,
	TRACE_HITTYPE_DYNENT_MODEL = 0x2,
	TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
	TRACE_HITTYPE_GLASS = 0x4,
};

struct trace_t
{
	float fraction;
	float surfaceDirection[3];
	int surfaceFlags;
	int contents;
	TraceHitType hitType;
	unsigned __int16 hitId;
	unsigned __int16 modelIndex;
	__int16 partName;
	unsigned __int16 partGroup;
	bool allsolid;
	bool startsolid;
	bool walkable;
	bool getPenetration;
	bool removePitchAndRollRotations;
};

