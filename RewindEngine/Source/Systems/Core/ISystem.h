/*

File: ISystem.h
Author: Esteban Maldonado
Date Created:

Modified by(optional):
Date Modified(optional):

Purpose(optional):

*/

#pragma once

#include<string>
#include<vector>

using std::string;
using std::vector;

//message base class - each system may interpret the message however they want
//You may create new Message classes that inherit from this
class Message
{
public:
	
	enum MessageType : short
	{
		/*
		Include all of the message types that you need here...
		*/
		
		MessageType_count
	};

	Message(MessageType mt):m_messageType(mt){}
	virtual ~Message(){}

	MessageType GetMessageType()const{return m_messageType;}

private:
	MessageType m_messageType;
};

class ISystem
{
public:

	ISystem() :m_isInitialized(false) {}

	virtual ~ISystem() {};

	virtual bool Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Unload() = 0;


	virtual void ReceiveMessage(Message * msg) = 0;
	
	//Getters
	virtual string GetName() const = 0;
	bool IsInitialized()const
	{ 
		return m_isInitialized; 
	}

protected:
	//NOTE: Please set this variable to true when the system is initialized...
	bool m_isInitialized;
};