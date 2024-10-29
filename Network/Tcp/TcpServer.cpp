//===============
// TcpServer.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "TcpServer.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//==================
// Con-/Destructors
//==================

TcpServer::TcpServer()
{}


//========
// Common
//========

VOID TcpServer::Listen(WORD port)
{
m_Socket=new TcpSocket();
m_Socket->Listen(port);
CreateTask(this, &TcpServer::DoListen);
}


//================
// Common Private
//================

VOID TcpServer::DoListen()
{
while(1)
	{
	Handle<TcpSocket> tcp_sock=m_Socket->Accept();
	if(!tcp_sock)
		break;
	ConnectionReceived(this, tcp_sock);
	}
}

}}