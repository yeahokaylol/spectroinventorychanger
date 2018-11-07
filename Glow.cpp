#include "Glow.h"

#include <unordered_map>
bool PaintTraverse_IsGoodPlayer_ESP(CBaseEntity* Target)
{
	if (!Target)
		return false;

	if (Target == Hacks.LocalPlayer)
		return false;

	if (Target->IsDormant())
		return false;

	if (!Target->IsPlayer())
		return false;

	if (Target->GetHealth() == 0)
		return false;

	if (!Target->isAlive())
		return false;


	return true;
}
Vector GetHitboxPOS_Ent(CBaseEntity* Player, int HitboxID)
{
	if (!Player)
		return Vector(0, 0, 0);

	matrix3x4 matrix[128];
	if (!Player->SetupBones(matrix, 128, 0x00000100, GetTickCount64())) return Vector(0, 0, 0);
	const model_t* mod = Player->GetModel();
	if (!mod) return Vector(0, 0, 0);
	studiohdr_t* hdr = Interfaces.g_pModelInfo->GetStudioModel(mod);
	if (!hdr) return Vector(0, 0, 0);
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	if (!set) return Vector(0, 0, 0);
	mstudiobbox_t* hitbox = set->pHitbox(HitboxID);
	if (!hitbox) return Vector(0, 0, 0);
	Vector vMin, vMax, vCenter, sCenter;
	g_Math.VectorTransform2(hitbox->bbmin, matrix[hitbox->bone], vMin);
	g_Math.VectorTransform2(hitbox->bbmax, matrix[hitbox->bone], vMax);
	vCenter = (vMin + vMax) *0.5f;
	return vCenter;
}
bool IsVisable(CBaseEntity* Target, int boneID)
{
	CBaseEntity* copy = Target;
	trace_t Trace;
	Vector start = Hacks.LocalPlayer->GetEyePosition();
	Vector end = GetHitboxPOS_Ent(Target, boneID);
	UTIL_TraceLine(start, end, MASK_SOLID, Hacks.LocalPlayer, 0, &Trace);
	if (Trace.m_pEnt == copy) return true;
	if (Trace.fraction == 1.0f) return true;
	return false;
}

DWORD GlowManagerZ = *(DWORD*)(Utils.FindPatternIDA("client.dll", "0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00") + 3);

void GlowEsp::DrawGlow()
{
	CGlowObjectManager* GlowObjectManager = (CGlowObjectManager*)GlowManagerZ;

	CGlowObjectManager::GlowObjectDefinition_t* glowEntity;
	if (g_Options.Visuals.Vis_Glow) {
		for (int i = 0; i < GlowObjectManager->size; i++)
		{
			glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
			CBaseEntity* Entity = glowEntity->getEntity();

			if (!Entity) continue;

			ClientClass* cClass = (ClientClass*)Entity->GetClientClass();

			if (cClass->m_ClassID == (int)CSGOClassID::CCSPlayer)
			{
				if (!PaintTraverse_IsGoodPlayer_ESP(Entity))
					continue;

				int Red;
				int Blue;
				int Green;
				int Alpha;
				bool seeable = IsVisable(Entity, 0);

				if (Entity->GetTeam() == Hacks.LocalPlayer->GetTeam()) {
					if (!seeable) {

						Red = 50;
						Green = 255;
						Blue = 50;
						Alpha = 255;
						if (g_Options.Visuals.Vis_Glow_Vis && g_Options.Visuals.Vis_Glow_Team) {
							glowEntity->set(CColor(Red, Green, Blue, Alpha));

						}

					}
					else {
						Red = 0;
						Green = 255;
						Blue = 0;
						Alpha = 255;
						if (g_Options.Visuals.Vis_Glow_Team)
							glowEntity->set(CColor(Red, Green, Blue, Alpha));

					}

				}
				else {
					if (!seeable) {

						Red = 255;
						Green = 50;
						Blue = 50;
						Alpha = 255;
						if (g_Options.Visuals.Vis_Glow_Vis) {
							glowEntity->set(CColor(Red, Green, Blue, Alpha));

						}
					}
					else {
						Red = 255;
						Green = 0;
						Blue = 0;
						Alpha = 255;
						glowEntity->set(CColor(Red, Green, Blue, Alpha));

					}

				}
			}
		}
	}


}



