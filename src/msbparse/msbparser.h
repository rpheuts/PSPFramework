#ifndef MSBPARSER_H_
#define MSBPARSER_H_

#include "msbpage.h"
#include "msblesson.h"

class MSBParser
{
	public:
		MSBParser();
		~MSBParser();
		MSBLesson* Parse(string file);

	
};

#endif
