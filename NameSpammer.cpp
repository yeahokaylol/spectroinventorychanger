#include "stdafx.h"
#include <chrono>
CNameChanger* g_pNameChanger = new CNameChanger();
void StdReplaceStr2(std::string& replaceIn, const std::string& replace, const std::string& replaceWith)
{
	size_t const span = replace.size();
	size_t const step = replaceWith.size();
	size_t index = 0;

	while (true)
	{
		index = replaceIn.find(replace, index);

		if (index == std::string::npos)
			break;

		replaceIn.replace(index, span, replaceWith);
		index += step;
	}
}
void CNameChanger::BeginFrame()
{
	static bool flip = false;

	if (!g_Options.Misc.NameChangerenabled)
		return;

	if (!Interfaces.pEngine->IsInGame())
		return;

	if (changes >= 5)
	{
		changes = -1;
		flip = false;
		g_Options.Misc.NameChangerenabled = false;
		return;
	}

	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()).count();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp < 100)
		return;

	timeStamp = currentTime_ms;

	changes++;

	if (changes < 5)
	{
		std::string ctWithEscapesProcessed1 = std::string(nickname);
		std::string ctWithEscapesProcessed2 = std::string(separator);

		StdReplaceStr2(ctWithEscapesProcessed1, "\\n", "\n");
		StdReplaceStr2(ctWithEscapesProcessed2, "\\n", "\n");

		char buf[128];

		if (g_Options.Misc.NameChangerseparator_animation == 0)
		{
			if (!flip)
			{
				sprintf(buf, "%s%s", ctWithEscapesProcessed2.c_str(), ctWithEscapesProcessed1.c_str());
			}
			else
			{
				sprintf(buf, "%s", ctWithEscapesProcessed1.c_str());
			}
		}
		else if (g_Options.Misc.NameChangerseparator_animation == 1)
		{
			if (!flip)
			{
				sprintf(buf, "%s%s", ctWithEscapesProcessed1.c_str(), ctWithEscapesProcessed2.c_str());
			}
			else
			{
				sprintf(buf, "%s", ctWithEscapesProcessed1.c_str());
			}
		}
		else
		{
			if (!flip)
			{
				sprintf(buf, "%s%s", ctWithEscapesProcessed1.c_str(), ctWithEscapesProcessed2.c_str());
			}
			else
			{
				sprintf(buf, "%s%s", ctWithEscapesProcessed2.c_str(), ctWithEscapesProcessed1.c_str());
			}
		}

		this->ChangeName(buf);
		flip = !flip;
	}
}