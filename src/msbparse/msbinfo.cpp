#include "../framework.h"

MSBInfo::MSBInfo()
{

}

MSBInfo::~MSBInfo()
{

}

MSBInfoPage* MSBInfo::Parse(TiXmlNode* page)
{
	if (page)
	{
		_page = new MSBInfoPage();

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

		// Navigate to the 'background' part while adding skills
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
			if (child->ValueStr().compare("backgroundInfo") == 0)
			{
				// Handle background node
				XMLProcessBackground(child);
			}
		}
	
	}
	else
		Core::Dbg->Log(Warning, "XML parse error, no page element found");

	return _page;
}

void MSBInfo::XMLProcessBackground(TiXmlNode* bg)
{
	if (bg)
	{
		TiXmlNode* child = 0;
		_page->Text = "";
		while((child = bg->IterateChildren(child)))
		{
			if (child->ValueStr().compare("avobject") == 0)
			{
				TiXmlElement* av = child->ToElement();
				_page->Image = av->Attribute("filename");
			}
			if (child->ValueStr().compare("txt") == 0)
			{
				TiXmlElement* txt = child->ToElement();
				_page->Text += txt->GetText();
			}
		}
	}
	else
		Core::Dbg->Log(Warning, "NULL value passed to utterance node handler");
}
