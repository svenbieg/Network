//================
// UdpMessage.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "UdpMessage.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Udp {


//==================
// Con-/Destructors
//==================

UdpMessage::UdpMessage(VOID const* buf, WORD size):
m_Buffer(nullptr),
m_Size(0)
{
if(size==0)
	return;
m_Buffer=new BYTE[size];
CopyMemory(m_Buffer, buf, size);
m_Size=size;
}

UdpMessage::~UdpMessage()
{
if(m_Buffer)
	delete m_Buffer;
}

}}
