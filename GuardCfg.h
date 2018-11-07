#pragma once
#include <xstring>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <vector>


template <typename T>
class ConfigValueProtect
{
public:
	ConfigValueProtect(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};

class CConfigProtect
{
protected:
	std::vector<ConfigValueProtect<std::string>*> chars;

private:
	void SetupValue(std::string& labal, std::string def, std::string, std::string);
public:
	CConfigProtect()
	{
		Setup();
	}

	void Setup();

	void Load();


	char login_buf[64] = "Login";
	char password_buf2[64] = "Password";

	std::string login_buf2;
	std::string password_buf22;
};

extern CConfigProtect* pConfigProtect;

