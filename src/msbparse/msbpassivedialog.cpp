#include "msbparse.h"

MSBPassiveDialog::MSBPassiveDialog()
{
	
}

MSBPassiveDialog::~MSBPassiveDialog()
{
	
}

MSBPassiveDialogPage* MSBPassiveDialog::Parse(TiXmlNode* page)
{	
	if (page)
	{
		_page = new MSBPassiveDialogPage();
		TiXmlNode* child = 0;
		TiXmlNode* pdchild = 0;
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

		// Navigate to the 'practicedialog' part
		while((pdchild = root->IterateChildren( pdchild )))
		{
			if (pdchild->ValueStr().compare("skill") == 0)
			{
				TiXmlElement* skillelement = pdchild->ToElement();
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
			if (pdchild->ValueStr().compare("practicedialog") == 0)
			{
				// Navigate to 'sp' part
				page = pdchild->FirstChild("tlscript");
				while((child = page->IterateChildren(child)))
				{
					if (child->ValueStr().compare("sp") == 0)
					{
						XMLProcessSP(child);
					}
				}
			}
		}
	
	}
	else
		Core::Dbg->Log(Warning, "XML parse error, no page");

	return _page;
}

void MSBPassiveDialog::XMLProcessSP(TiXmlNode* sp)
{
	// Print some stuff to the screen
	TiXmlNode* child = 0;
	Sentence* sent = new Sentence();

	while( (child = sp->IterateChildren( child )))
	{
		if (child->ValueStr().compare("speaker") == 0)
		{
			// Speaker tag found
			TiXmlElement* txt = child->ToElement();
			if (txt)
				sent->Speaker =  txt->GetText();
			else
				Core::Dbg->Log(Warning, "Node conversion error");
		}
		if (child->ValueStr().compare("snt") == 0)
		{
			// Sentence tag found ('snt')
			TiXmlNode* foreign = child->FirstChild("channel");
			TiXmlNode* english = foreign->NextSibling("channel");
			
			if (foreign && english)
			{
				TiXmlElement* forElement = foreign->FirstChild("txt")->ToElement();
				TiXmlElement* engElement = english->FirstChild("txt")->ToElement();
				
				if (forElement && engElement)
				{
					// Current elements contain the actual text
					sent->Foreign = forElement->GetText();
					sent->English = engElement->GetText();
				}
				else
					Core::Dbg->Log(Warning, "Conversion error in SNT node");
			}
			else
				Core::Dbg->Log(Warning, "Missing part of SNT node");
		}
	}
	_page->Sentences.push_back(sent);
}
