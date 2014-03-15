#ifndef PASSIVEDIALOG_H_
#define PASSIVEDIALOG_H_

#include "msbparse.h"

class MSBPassiveDialog
{
	public:
		MSBPassiveDialog();
		~MSBPassiveDialog();
		MSBPassiveDialogPage* Parse(TiXmlNode* page);

	private:
		void XMLProcessSP(TiXmlNode* sp);

	private:
		MSBPassiveDialogPage* _page;
};

#endif
