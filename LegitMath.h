#include "Tools/Utils/hitbox.h"
#include <xmmintrin.h>
class LegitMath
{
private:
	static void inline SinCos(float radians, float* sine, float* cosine)
	{
		*sine = sin(radians);
		*cosine = cos(radians);
	}
	/*static inline float FASTSQRT(float x)
	{
		unsigned int i = *(unsigned int*)&x;

		i += 127 << 23;
		// approximation of square root
		i >>= 1;
		return *(float*)&i;
	}*/
	static inline float FASTSQRT(float x)
	{
		__m128 root = _mm_sqrt_ss(_mm_load_ss(&x));
		return *(reinterpret_cast<float*>(&root));
	}
public:

	static float GetDamageZ(const Vector& point, FireBulletData fbd)
	{
		float damage = 0.f;
		

		damage = Autowall::GetDamageData(point, fbd);

		

		return damage;

		/*float damage = 0.f;
		damage = Autowall::GetDamageData(point, fbd);
		return damage;*/
	}
	static void VectorAngles(const Vector& forward, Vector& angles)
	{
		if (forward[1] == 0.0f && forward[0] == 0.0f)
		{
			angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
			angles[1] = 0.0f;
		}
		else
		{
			angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
			angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

			if (angles[1] > 90) angles[1] -= 180;
			else if (angles[1] < 90) angles[1] += 180;
			else if (angles[1] == 90) angles[1] = 0;
		}

		angles[2] = 0.0f;
	}

	static void AngleVectors(const Vector& angles, Vector* forward)
	{
		float sp, sy, cp, cy;

		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);

		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}
	static void AngleVectorsI(const Vector &angles, Vector& forward)
	{
		Assert(s_bMathlibInitialized);
		Assert(forward);

		float sp, sy, cp, cy;

		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}
	static Vector CalcAngle(Vector src, Vector dst)
	{
		Vector angles;
		Vector delta = src - dst;
		angles.x = (asinf(delta.z / delta.Length()) * 57.295779513082f);
		angles.y = (atanf(delta.y / delta.x) * 57.295779513082f);
		angles.z = 0.0f;
		if (delta.x >= 0.0) { angles.y += 180.0f; }

		return angles;
	}
	static float GetFov(const Vector& qView, const Vector& qAim) //change to calcangle
	{
		Vector angle, aim;

		AngleVectors(qView, &aim);
		AngleVectors(qAim, &angle);

		return RAD2DEG(acos(aim.Dot(angle) / aim.LengthSqr()));
	}

	static float VectorDistance(Vector v1, Vector v2)
	{
		return FASTSQRT(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
	}
};