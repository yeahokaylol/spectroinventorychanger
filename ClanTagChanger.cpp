#include "ClanTagChanger.h"
#include <stdio.h> 
#include <ctime>
#include <chrono>
#include "hooks.h"

CClantagChanger* g_pClanTagChanger = new CClantagChanger;
CClantagChanger::Animation CClantagChanger::Marquee(std::string name, std::string text, int width /*= 15*/)
{
	// Outputs cool scrolling text animation
	char empty = ' ';
	std::replace(text.begin(), text.end(), ' ', empty);

	std::string cropString = std::string(width, empty) + text + std::string(width - 1, empty);

	std::vector<CClantagChanger::Frame> frames;
	for (unsigned long i = 0; i < text.length() + width; i++)
		frames.push_back(CClantagChanger::Frame(cropString.substr(i, width + i), g_Options.Misc.ClantagChanger.animation_speed));

	return CClantagChanger::Animation(name, frames, CClantagChanger::ANIM_LOOP);
}

std::vector<std::string> splitWords(std::string text)
{
	std::istringstream stream(text);
	std::string word;
	std::vector<std::string> words;
	while (stream >> word)
		words.push_back(word);

	return words;
}

CClantagChanger::Animation CClantagChanger::Words(std::string name, std::string text)
{
	// Outputs a word by word animation
	std::vector<std::string> words = splitWords(text);
	std::vector<CClantagChanger::Frame> frames;
	for (unsigned long i = 0; i < words.size(); i++)
		frames.push_back(Frame(words[i], g_Options.Misc.ClantagChanger.animation_speed));

	return CClantagChanger::Animation(name, frames, CClantagChanger::ANIM_LOOP);
}

CClantagChanger::Animation CClantagChanger::Letters(std::string name, std::string text)
{
	// Outputs a letter incrementing animation
	std::vector<CClantagChanger::Frame> frames;
	for (unsigned long i = 1; i <= text.length(); i++)
		frames.push_back(Frame(text.substr(0, i), g_Options.Misc.ClantagChanger.animation_speed));

	for (unsigned long i = text.length() - 2; i > 0; i--)
		frames.push_back(Frame(frames[i].text, g_Options.Misc.ClantagChanger.animation_speed));

	return CClantagChanger::Animation(name, frames, CClantagChanger::ANIM_LOOP);
}

void CClantagChanger::UpdateClanTagCallback()
{
	if (strlen(g_Options.Misc.ClantagChanger.value) > 0 && g_Options.Misc.ClantagChanger.type > STATIC)
	{
		std::string ct = g_Options.Misc.ClantagChanger.value;
		switch (g_Options.Misc.ClantagChanger.type)
		{
		case MARQUEE:
			*CClantagChanger::animation = CClantagChanger::Marquee(XorStr("CUSTOM"), ct);
			break;
		case WORDS:
			*CClantagChanger::animation = CClantagChanger::Words(XorStr("CUSTOM"), ct);
			break;
		case LETTERS:
			*CClantagChanger::animation = CClantagChanger::Letters(XorStr("CUSTOM"), ct);
			break;
		}

		return;
	}

	CClantagChanger::animations = {
		CClantagChanger::Marquee(XorStr("SpectroFobia"), XorStr("SpectroFobia")),
		CClantagChanger::Words(XorStr("SpectroFobia"), XorStr("SpectroFobia")),
		CClantagChanger::Letters(XorStr("SpectroFobia"), XorStr("SpectroFobia"))
	};

	int current_animation = g_Options.Misc.ClantagChanger.type - 1;
	if (current_animation >= 0)
		CClantagChanger::animation = &CClantagChanger::animations[current_animation];
}
void StdReplaceStr(std::string& replaceIn, const std::string& replace, const std::string& replaceWith)
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
void CClantagChanger::BeginFrame()
{
	if (!g_Options.Misc.ClantagChanger.enabled)
		return;
	if (!Interfaces.pEngine->IsInGame())
		return;
	if (!Interfaces.pEngine->IsConnected())
		return;

	static auto pSetClanTag = reinterpret_cast< void(__fastcall*)(const char*, const char*) >((DWORD)(Utils.FindPatternIDA("engine.dll", "53 56 57 8B DA 8B F9 FF 15")));

	if (g_Options.Misc.ClantagChanger.type == CTTIME)
	{
		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);
		char buffer[30];
		sprintf(buffer, "[%02d:%02d:%02d]", now->tm_hour, now->tm_min, now->tm_sec);

		pSetClanTag(buffer, "LOCALTIME");
		return;
	}

	if (strlen(g_Options.Misc.ClantagChanger.value) == 0 && g_Options.Misc.ClantagChanger.type == STATIC)
		return;

	long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()).count();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp > CClantagChanger::animation->GetCurrentFrame().time)
	{
		timeStamp = currentTime_ms;
		CClantagChanger::animation->NextFrame();
	}

	std::string ctWithEscapesProcessed = g_Options.Misc.ClantagChanger.value;
	StdReplaceStr(ctWithEscapesProcessed, "\\n", "\n"); // compute time impact? also, referential so i assume RAII builtin cleans it up...
	pSetClanTag(g_Options.Misc.ClantagChanger.type == STATIC ? ctWithEscapesProcessed.c_str() : CClantagChanger::animation->GetCurrentFrame().text.c_str(), "SpectroFobia");
}
