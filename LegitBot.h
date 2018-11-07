class CLegitClass
{
public:
	void Run(CUserCmd* pCmd, CBaseCombatWeapon* weap);
private:

	void Run_Aim(CUserCmd * cmd);
	
	void Triggerbot();
	int FindTarget(CUserCmd* pCmd, Vector Rcs, Vector& NextBonePos);

	static float RandomFloat(float a, float b)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
	//int m_fbestfov;
	//int m_ibesttarget;
}; extern CLegitClass* g_pLegitbot;