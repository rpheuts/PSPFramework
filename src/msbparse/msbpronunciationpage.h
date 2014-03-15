#ifndef MSBPRONUNCIATIONPAGE_H_
#define MSBPRONUNCIATIONPAGE_H_

#include "msbparser.h"

class MSBPronunciationPage : public MSBPage
{
	public:
		list<Utterance*> Utterances;
};

#endif
