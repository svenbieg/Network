//==============
// UdpMessage.h
//==============

#pragma once


//===========
// Namespace
//===========

namespace Network {
	namespace Udp {


//=============
// Udp-Message
//=============

class UdpMessage: public Object
{
public:
	// Con-/Destructors
	UdpMessage(VOID const* Buffer, WORD Size);
	~UdpMessage();

	// Common
	VOID const* Begin()const { return m_Buffer; }
	WORD GetSize()const { return m_Size; }

private:
	// Common
	BYTE* m_Buffer;
	WORD m_Size;
};

}}
