#ifndef MSBPAGE_H_
#define MSBPAGE_H_

#include "../framework.h"

class Skill
{
	public:
		string ID;
		string Name;
};

class MSBPage
{
	public:
		string EID;
		string Category;
		string Type;
		string NodeName;
		string Title;
		list<Skill*> Skills;
};

#endif
