#pragma once
#include "stdafx.h"

template <typename T>
class ConfigItemZ
{
	std::string category, name;
	T* value;
public:
	ConfigItemZ(std::string category, std::string name, T* value)
	{
		this->category = category;
		this->name = name;
		this->value = value;
	}
};

template <typename T>
class ConfigValue
{
public:
	ConfigValue(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};

class CConfig
{
protected:
	std::vector<ConfigValue<int>*> ints;
	std::vector<ConfigValue<bool>*> bools;
	std::vector<ConfigValue<float>*> floats;
	std::vector<ConfigValue<char>*> chars;

private:
	void SetupValue(int&, int, std::string, std::string);
	void SetupValue(bool&, bool, std::string, std::string);
	void SetupValue(float&, float, std::string, std::string);
	void SetupValue(char&, char, std::string, std::string);
public:
	CConfig()
	{
		Setup();
	}

	void Setup();

	void Save(CFGTYPE Type);
	void Delete(CFGTYPE Type);
	void Load(CFGTYPE Type);
	void Rename(char* newname, CFGTYPE Type);


};

extern CConfig* pConfig;