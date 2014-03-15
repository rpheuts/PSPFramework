#include "../framework.h"

DebugMessage::DebugMessage(DebugType type, string message, int timeStamp)
{
	Type = type;
	Message = message;
	TimeStamp = timeStamp;
}

Debug::Debug()
{
	Log(Init, "Logging enabled...");
}

Debug::~Debug()
{
	_messageList.clear();
}

void Debug::Log(DebugType type, string message)
{
	DebugMessage* msg = new DebugMessage(type, message, 0);
	_messageList.push_back(msg);
}

void Debug::Log(DebugMessage* msg)
{
	_messageList.push_back(msg);
}

DebugMessage* Debug::Pop()
{
	if (_messageList.size() > 0)
	{
		DebugMessage* msg = _messageList.front(); 
		_messageList.pop_front();
		return msg;
	}
	else
		return NULL;
}
