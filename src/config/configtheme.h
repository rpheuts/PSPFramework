#ifndef CONFIGTHEME_H
#define CONFIGTHEME_H

#include "../framework.h"

class ConfigTheme : public Config {
	public:
		ConfigTheme();
		string GetPathValue(string key);
		string GetValue(string key);
		void SetValue(string key, string value);
		
	public:
		string ImagesCorePath;
		string ImagesBootPath;
		string IconConfig;
		string ThemeDir;
};
#endif
