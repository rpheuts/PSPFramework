#ifndef TECHDEMO_H_
#define TECHDEMO_H_

#include "../framework.h"
class TechDemo : public WindowApp
{
	public:
		TechDemo();
		~TechDemo();
		void HandleController(int mouseX, int mouseY, int btn);
		void HandleInputEvent(string EventID, string arg);
		void Destroy();
		void Render();
		void RenderFullscreen();
		void ProcessDebug();
		void XMLParse(string file);
		void XMLProcessSP(TiXmlNode* sp);
		void RenderPassiveDialogPage(MSBPage* page);
		void RenderPronunciation(MSBPage* page);
		void RenderInfoPage(MSBPage* page);
		
	private:
		int _over;
		int _playing;
		int _xml;
		int _posX;
		int _posY;
		int _update;
		Image* _audioBtn;
		Image* _audioBtnOver;
		Image* _test;
		MSBInterfaceManager* _interface;
		MSBLesson* _lesson;
		list<MSBPage*>::iterator _curPage;
};
#endif
