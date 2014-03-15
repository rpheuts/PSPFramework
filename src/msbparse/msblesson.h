#ifndef LESSON_H_
#define LESSON_H_

#include "msbparse.h"

class MSBLesson
{
	public:
		string ID;
		string Title;
		list<MSBPage*> Pages;
};

#endif
