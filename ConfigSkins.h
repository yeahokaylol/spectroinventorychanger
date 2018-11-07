#pragma once
#include "stdafx.h"

template <typename T>
class ConfigItemZSkinz
{
	std::string category, name;
	T* value;
public:
	ConfigItemZSkinz(std::string category, std::string name, T* value)
	{
		this->category = category;
		this->name = name;
		this->value = value;
	}
};



template <typename T>
class ConfigValueSkins
{
public:
	ConfigValueSkins(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};
class CConfigSkins
{
protected:
	std::vector<ConfigValueSkins<int>*> ints;
	std::vector<ConfigValueSkins<bool>*> bools;
	std::vector<ConfigValueSkins<float>*> floats;
	std::vector<ConfigValueSkins<char>*> chars;

private:
	void SetupValue(int&, int, std::string, std::string);
	void SetupValue(bool&, bool, std::string, std::string);
	void SetupValue(float&, float, std::string, std::string);
	void SetupValue(char&, char, std::string, std::string);
public:
	CConfigSkins()
	{
		Setup();
	}

	void Setup();

	void Save(CFGTYPE Type);
	void Delete(CFGTYPE Type);
	void Load(CFGTYPE Type);
	void Rename(char* newname, CFGTYPE Type);


};

extern CConfigSkins* pConfigSkins;