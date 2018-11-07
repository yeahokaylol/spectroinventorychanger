class CNameChanger
{
public:
	void BeginFrame();

	char* nickname;
	char* separator;
	static void ChangeName(const char* name)
	{
		ConVar* nameConvar = Interfaces.g_ICVars->FindVar(XorStr("name"));
		*(int*)((DWORD)&nameConvar->m_fnChangeCallbacks + 0xC) = NULL;
		nameConvar->SetValue(name);
	};
private:
	int changes = -1;
}; extern CNameChanger* g_pNameChanger;