#ifndef MSBINFO_H_
#define MSBINFO_H_

#include "msbparse.h"

class MSBInfo
{
	public:
		MSBInfo();
		~MSBInfo();
		MSBInfoPage* Parse(TiXmlNode* page);

	private:
		void XMLProcessBackground(TiXmlNode* utt);

	private:
		MSBInfoPage* _page;
};

#endif
