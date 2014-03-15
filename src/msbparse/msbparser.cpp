#include "msbparse.h"

MSBParser::MSBParser()
{
	
}

MSBParser::~MSBParser()
{

}

MSBLesson* MSBParser::Parse(string file)
{
	// Init our parsers
	MSBPassiveDialog* _pdParser = new MSBPassiveDialog();
	MSBPronunciation* _pParser = new MSBPronunciation();
	MSBInfo* _iParser = new MSBInfo();

	TiXmlDocument doc(file);
	bool loadOkay = doc.LoadFile();
	MSBLesson* lesson = new MSBLesson();

	if (loadOkay)
	{
		TiXmlNode* node = doc.FirstChild("lesson");
		if (node)
		{
			TiXmlNode* pagechild = 0;

			// Navigate to the 'page' part
			while((pagechild = node->IterateChildren(pagechild)))
			{
				if (pagechild->ValueStr().compare("page") == 0)
				{
					TiXmlElement* pageElement = pagechild->ToElement();
					string category = pageElement->Attribute("category");
					if (category.compare("PassiveDialog") == 0)
					{
						MSBPage* page = _pdParser->Parse(pageElement);
						lesson->Pages.push_back(page);
					}
					if (category.compare("Pronunciation") == 0)
					{						
						lesson->Pages.push_back(_pParser->Parse(pageElement));
					}
					if (category.compare("Info") == 0)
					{						
						lesson->Pages.push_back(_iParser->Parse(pageElement));
					}
				}
			}
		}
		else
			Core::Dbg->Log(Warning, "Lesson node not found");
	}
	else
		Core::Dbg->Log(Warning, "XML document failed to open");
	return lesson;
}
