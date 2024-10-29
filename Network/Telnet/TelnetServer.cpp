//==================
// TelnetServer.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "TelnetServer.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Telnet {


//==================
// Con-/Destructors
//==================

TelnetServer::TelnetServer()
{}


//========
// Common
//========

VOID TelnetServer::Listen(WORD port)
{
m_Socket=new TcpSocket();
m_Socket->Listen(port);
CreateTask(this, &TelnetServer::DoListen);
}


//================
// Common Private
//================

VOID TelnetServer::DoListen()
{
}

}}