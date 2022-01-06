#pragma once

#define M_PI					3.14159265358979323846f
#define M_E						2.71828182845904523536f

#define	PITCH					0		// up / down
#define	YAW						1		// left / right
#define	ROLL					2		// fall over

#define WIDTH					0
#define HEIGHT					1

#define	ANGLE2SHORT(x)			((int)((x)*65536/360) & 65535)
#define	SHORT2ANGLE(x)			((x)*(360.0/65536))
#define ANG_CLIP(ang)			if(ang>180.0f)ang-=360.0f;else if(ang<-180.0f)ang+=360.0f

#define METERS					0
#define FEETS					1
#define YARDS					2

#define VMETERS					30.0f
#define VFEETS					VMETERS / 3.28083989501312f
#define VYARDS					VMETERS / 1.0936133f	

#define POW(x)((x)*(x))
#define VectorLength(a)         sqrt(POW((a)[0])+POW((a)[1])+POW((a)[2]))
#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define VectorCopy4(a,b)		((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2],(b)[3]=(a)[3])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorCmp(a,b)			(((a)[0]==(b)[0])&&((a)[1]==(b)[1])&&((a)[2]==(b)[2]))
#define VectorDistance(a,b)		(sqrt(POW(a[0]-b[0]) + POW(a[1]-b[1]) + POW(a[2]-b[2])))
#define	CMD_BACKUP	128	
#define	CMD_MASK (CMD_BACKUP - 1)
#define IN_ATTACK ( 1 << 0 )
#define VectorLength(a)         sqrt(POW((a)[0])+POW((a)[1])+POW((a)[2]))
#define VectorDivide			(v, s, o)((o)[0]=(v)[0]/=(s),(o)[1]=(v)[1]/=(s),(o)[2]=(v)[2]/=(s))
#define VectorNormalize(a)      {vec_t l=VectorLength(a);(a)[0]/=l;(a)[1]/=l;(a)[2]/=l;}
#define VectorMul(a,scale)		{(a)[0] *= scale; (a)[1] *= scale; (a)[2] *= scale;}

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
//comment

class Vector
{
public:
	// Construction/destruction
	inline Vector(void) { }
	inline Vector(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	inline Vector(double X, double Y, double Z) { x = (float)X; y = (float)Y; z = (float)Z; }
	inline Vector(int X, int Y, int Z) { x = (float)X; y = (float)Y; z = (float)Z; }
	inline Vector(const Vector& v) { x = v.x; y = v.y; z = v.z; }
	inline Vector(float rgfl[3]) { x = rgfl[0]; y = rgfl[1]; z = rgfl[2]; }

	// Operators
	inline Vector operator-(void) const { return Vector(-x, -y, -z); }
	inline int operator==(const Vector& v) const { return x == v.x && y == v.y && z == v.z; }
	inline int operator!=(const Vector& v) const { return !(*this == v); }
	inline Vector operator+(const Vector& v) const { return Vector(x + v.x, y + v.y, z + v.z); }
	inline Vector operator-(const Vector& v) const { return Vector(x - v.x, y - v.y, z - v.z); }
	inline Vector operator*(float fl) const { return Vector(x*fl, y*fl, z*fl); }
	inline float Vector::operator*(const Vector& other) const //idk why I wrote this so weirdly, mustve been a long time ago
	{
		return x * other.x + y * other.y + z * other.z;
	}
	inline Vector operator/(float fl) const { return Vector(x / fl, y / fl, z / fl); }
	void operator += (const Vector& add) { x += add.x; y += add.y; z += add.z; }
	void operator -= (const Vector& sub) { x -= sub.x; y -= sub.y; z -= sub.z; }
	void operator *= (const float mul) { x *= mul; y *= mul; z *= mul; }
	void operator /= (const float mul) { x /= mul; y /= mul; z /= mul; }

	// Methods
	inline void CopyToArray(float* rgfl) const { rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; }
	inline float Length(void) const { return (float)sqrt(x*x + y*y + z*z); }
	operator float *() { return &x; } // Vectors will now automatically convert to float * when needed
	operator const float *() const { return &x; } // Vectors will now automatically convert to float * when needed
	inline Vector Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector(x * flLen, y * flLen, z * flLen);
	}

	inline Vector CrossProduct(const Vector & other)
	{
		return
		{
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		};
	}

	inline float Length2D(void) const { return (float)sqrt(x*x + y*y); }

	__forceinline void ClampAngles()
	{
		if (x > 180) { x -= 360; }
		if (x < -180) { x += 360; }
		if (y > 180) { y -= 360; }
		if (y < -180) { y += 360; }
	}

	// Members
	vec_t x, y, z;
};
inline Vector operator*(float fl, const Vector& v) { return v * fl; }

#pragma once
