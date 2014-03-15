#include "../framework.h"

MSBPronunciation::MSBPronunciation()
{

}

MSBPronunciation::~MSBPronunciation()
{

}

MSBPronunciationPage* MSBPronunciation::Parse(TiXmlNode* page)
{
	if (page)
	{
		_page = new MSBPronunciationPage();

		TiXmlNode* child = 0;
		TiXmlNode* root = page;
		TiXmlElement* pageElement = page->ToElement();
		
		if (pageElement)
		{
			_page->EID = pageElement->Attribute("eid");
			_page->Category = pageElement->Attribute("category");
			_page->Type = pageElement->Attribute("type");
			_page->NodeName = pageElement->Attribute("nodeName");

			TiXmlNode* title = page->FirstChild("title");
			if (title)
				_page->Title = title->ToElement()->GetText();
			else
				Core::Dbg->Log(Warning, "No title node found");
		}
		else
			Core::Dbg->Log(Warning, "Page node not accessible");
		pageElement = 0;

		// Navigate to the 'utt' part while adding skills
		while((child = root->IterateChildren(child)))
		{
			if (child->ValueStr().compare("skill") == 0)
			{
				TiXmlElement* skillelement = child->ToElement();
				if (skillelement)
				{
					Skill* sk = new Skill();
					sk->ID = skillelement->Attribute("kid");
					sk->Name = skillelement->GetText();
					_page->Skills.push_back(sk);
				}
				else
					Core::Dbg->Log(Warning, "Conversion error in Skill node");
			}
			if (child->ValueStr().compare("utt") == 0)
			{
				// Handle utt node
				XMLProcessUtt(child);
			}
		}
	
	}
	else
		Core::Dbg->Log(Warning, "XML parse error, no page element found");

	return _page;
}

void MSBPronunciation::XMLProcessUtt(TiXmlNode* utt)
{
	if (utt)
	{
		TiXmlNode* child = 0;
		TiXmlNode* sntchild = 0;
		TiXmlNode* snt = 0;
		Utterance* utterance = new Utterance();

		while((child = utt->IterateChildren(child)))
		{
			if (child->ValueStr().compare("note") == 0)
			{
				TiXmlElement* txt = child->FirstChild()->ToElement();
				if (txt)
				{
					utterance->Note = txt->GetText();
				}
			}

			if (child->ValueStr().compare("snt") == 0)
			{
				snt = child;
				while((sntchild = snt->IterateChildren(sntchild)))
				{
					TiXmlElement* chan = sntchild->ToElement();
					if (chan)
					{
						string lang = chan->Attribute("lang");
						
						if (lang.compare(LANGUAGE) == 0)
						{
							string type = chan->Attribute("contenttype");
							if (type.compare("text/plain") == 0)
								utterance->Foreign = chan->FirstChild("txt")->ToElement()->GetText();
							else if (type.compare("audio/wav") == 0)
							{
								if (!chan->Attribute("speed"))
									utterance->Audio = chan->FirstChild("avobject")->ToElement()->Attribute("filename");
							}
						}
						else if (lang.compare("en") == 0)
							utterance->English = chan->FirstChild("txt")->ToElement()->GetText();
					}
					else
						Core::Dbg->Log(Warning, "Malformed channel node, skipping...");
				}
			}
		}
		_page->Utterances.push_back(utterance);
	}
	else
		Core::Dbg->Log(Warning, "NULL value passed to utterance node handler");
}
