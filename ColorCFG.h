#pragma once
#include "stdafx.h"



template <typename T>
class ConfigValueColors
{
public:
	ConfigValueColors(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};
class CConfigColors
{
protected:
	std::vector<ConfigValueColors<int>*> ints;
	std::vector<ConfigValueColors<bool>*> bools;
	std::vector<ConfigValueColors<float>*> floats;
	std::vector<ConfigValueColors<char>*> chars;

private:
	void SetupValue(int&, int, std::string, std::string);
	void SetupValue(bool&, bool, std::string, std::string);
	void SetupValue(float&, float, std::string, std::string);
	void SetupValue(char&, char, std::string, std::string);
public:
	CConfigColors()
	{
		Setup();
	}

	void Setup();
	void DeclareSave(int col[4], std::string category);
	void Save();
	void Delete();
	void Load();
	void Rename(char* newname);


	int CTBoxVisable[4];
	int CTBoxInVisable[4];
	int TBoxVisable[4];
	int TBoxInVisable[4];

	int CTGlowVisable[4];
	int CTGlowInVisable[4];
	int TGlowVisable[4];
	int TGlowInVisable[4];

	int Beams[4];
	int FilledSpread[4];
	int LagCompHitboxes[4];
	int SoundESP[4];
	int DamageESP[4];
	int FakeAngleChams[4];
	int Stelki[4];
	int CTChamsVisable[4];
	int CTChamsInVisable[4];
	int TChamsVisable[4];
	int TChamsInVisable[4];

};

extern CConfigColors* pConfigColors;