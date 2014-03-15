/*
# PSP Framework 				
# ------------------------------------------------------------------
# Author: R.P.Heuts
# Date: 23-05-2006
# Version: 0.1
# 
# Class: Debug
# Desciption:
# Provides basic debugging support by logging messages, warnings and
# errors.
*/

#ifndef DEBUG_H_
#define DEBUG_H_

#include <list>

enum DebugType {Init, Error, Warning, Text};

class DebugMessage
{
	public:
		DebugType Type;
		string Message;
		int TimeStamp;
	
	public:
		DebugMessage(DebugType type, string message, int timeStamp);
	
};

class Debug
{
	public:
		Debug();
		~Debug();
		void Log(DebugType type, string message);
		void Log(DebugMessage* msg);
		DebugMessage* Pop();
		
		
	private:
		list<DebugMessage*> _messageList; 
};

#endif
