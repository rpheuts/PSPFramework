#ifndef MSBPRONUNCIATION_H_
#define MSBPRONUNCIATION_H_

#include "msbparse.h"

class MSBPronunciation
{
	public:
		MSBPronunciation();
		~MSBPronunciation();
		MSBPronunciationPage* Parse(TiXmlNode* page);

	private:
		void XMLProcessUtt(TiXmlNode* utt);

	private:
		MSBPronunciationPage* _page;
};

#endif
