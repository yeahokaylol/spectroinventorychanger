#include "stdafx.h"

struct backtrackData
{
	float simtime;
	Vector hitboxPos;
	
};

class legitBackTrackClass
{
	int latest_tick;
public:
	void legitBackTrack(CUserCmd* cmd, CBaseEntity* pLocal);
	void RageBackTrack(CUserCmd* cmd, CBaseEntity* pLocal);
private:

	static inline Vector angle_vector(Vector meme)
	{
		auto sy = sin(meme.y / 180.f * static_cast<float>(PI));
		auto cy = cos(meme.y / 180.f * static_cast<float>(PI));

		auto sp = sin(meme.x / 180.f * static_cast<float>(PI));
		auto cp = cos(meme.x / 180.f* static_cast<float>(PI));

		return Vector(cp*cy, cp*sy, -sp);
	}

	static inline float distance_point_to_line(Vector Point, Vector LineOrigin, Vector Dir)
	{
		auto PointDir = Point - LineOrigin;

		auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
		if (TempOffset < 0.000001f)
			return FLT_MAX;

		auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

		return (Point - PerpendicularPoint).Length();
	}

};

extern backtrackData headPositions[64][12];

extern legitBackTrackClass* backtracking;




