#include "../framework.h"

ConfigTheme::ConfigTheme() : Config("")
{
	configFile = THEME_PATH + Core::Cfg->GetValue("theme") + THEME_FILE;
	ImagesCorePath = THEME_PATH + Core::Cfg->GetValue("theme") + "/core/";
	ImagesBootPath = THEME_PATH + Core::Cfg->GetValue("theme") + "/boot/";
	ThemeDir = THEME_PATH;
}

string ConfigTheme::GetPathValue(string key)
{
	if (key[0] == 'c')
		return ImagesCorePath + Config::GetValue(key);
	else if (key[0] == 'b')
		return ImagesBootPath + Config::GetValue(key);
	else return NULL;
}

string ConfigTheme::GetValue(string key)
{
	return Config::GetValue(key);
}

void ConfigTheme::SetValue(string key, string value)
{
	Config::SetValue(key, value);
}
