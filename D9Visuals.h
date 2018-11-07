#include "RenderD9.h"


namespace D9Visuals
{
	void Render();
	void DrawCrossHair(float size, D3DCOLOR color);
	void DrawName(CBaseEntity *entity);
	void DrawWeapon(CBaseEntity *entity);
	void DrawHealth(CBaseEntity *entity);
	void DrawBox(CBaseEntity *entity, int cType);
	void OutOfViewIndicatorCircle(CBaseEntity *entity);
	void DrawBoneESP(CBaseEntity *entity, int cType);
	void DrawBone(CBaseEntity *entity, matrix3x4 *pBoneToWorldOut, D3DCOLOR color);
	
	bool GetPlayerBox(CBaseEntity *entity, float &x, float &y, float &width, float &height, Vector offset = Vector(0, 0, 0));
	bool Filter(CBaseEntity *entity,bool& IsVis);

	void PunchAnglesToScreen(int height, int width, int FOV, int *resultX, int *resultY);

	extern bool canUseSetupBones;

	extern int PlayerNickVal[65];
	extern int PlayerAlpha[65];
	extern float PlayerBoxAlpha[65];

};
template<class T, class U>
inline T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}