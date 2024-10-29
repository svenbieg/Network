//===============
// UdpServer.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Buffer.h"
#include "UdpServer.h"

using namespace Storage;


//===========
// Namespace
//===========

namespace Network {
	namespace Udp {


//==================
// Con-/Destructors
//==================

UdpServer::UdpServer()
{}


//========
// Common
//========

VOID UdpServer::Listen(WORD port)
{
m_Socket=new UdpSocket();
m_Socket->Listen(port);
CreateTask(this, &UdpServer::DoListen);
}


//================
// Common Private
//================

VOID UdpServer::DoListen()
{
Handle<Buffer> buf=new Buffer(PAGE_SIZE);
while(1)
	{
	WORD read=m_Socket->Read(buf->Begin(), PAGE_SIZE);
	Handle<UdpMessage> msg=new UdpMessage(buf->Begin(), read);
	MessageReceived(this, msg);
	}
}

}}