#include "GuardCfg.h"
//#include "SDK.h"
#include <winerror.h>

#include <ShlObj_core.h>
#pragma comment(lib, "Shell32.lib")


void CConfigProtect::Setup()
{
	SetupValue(this->login_buf2, "Login", "Loader", "Login");
	SetupValue(this->password_buf22, "Password", "Loader", "Password");

}
void CConfigProtect::SetupValue(std::string& labal, std::string def, std::string category, std::string name)
{
	labal = def;
	chars.push_back(new ConfigValueProtect<std::string>(category, name, &labal));
}





void CConfigProtect::Load()
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Spectro[loadercache]\\%s.ini", "LoaderCache");
		folder = std::string(path) + ("\\Spectro[loadercache]\\");
		file = std::string(path) + szCmd;
	}

	CreateDirectoryA(folder.c_str(), NULL);

	char value_l[32] = { '\0' };


	for (auto value : chars)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = value_l;
	}

}





CConfigProtect* pConfigProtect = new CConfigProtect();





