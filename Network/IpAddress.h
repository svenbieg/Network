//=============
// IpAddress.h
//=============

#pragma once


//=======
// Using
//=======

#include "Variable.h"


//===========
// Namespace
//===========

namespace Network {


//============
// IP-Address
//============

class IpAddress: public TypedVariable<UINT>
{
public:
	// Con-/Destrucotrs
	IpAddress(UINT Address=0): IpAddress(nullptr, Address) {}
	IpAddress(BYTE A1, BYTE A2, BYTE A3, BYTE A4): IpAddress(nullptr, A1, A2, A3, A4) {}
	IpAddress(Handle<String> Name, UINT Address=0);
	IpAddress(Handle<String> Name, BYTE A1, BYTE A2, BYTE A3, BYTE A4);

	// Access
	operator UINT() { return Get(); }
	Handle<String> ToString()override;
	static Handle<String> ToString(UINT Address);

	// Modification
	BOOL FromString(Handle<String> Address, BOOL Notify=true)override;

	// Common
	static UINT From(BYTE A1, BYTE A2, BYTE A3, BYTE A4);
};

}


//===================
// Handle IP-Address
//===================

template <>
class Handle<Network::IpAddress>
{
private:
	// Using
	using _ip_t=Network::IpAddress;

public:
	// Friends
	template <class _friend_t> friend class Handle;

	// Con-/Destructors
	Handle(): m_Object(nullptr) {}
	Handle(_ip_t* Object) { HandleCreate(&m_Object, Object); }
	Handle(Handle<_ip_t> const& Handle) { HandleCreate(&m_Object, Handle.m_Object); }
	Handle(Handle<_ip_t>&& Handle): m_Object(Handle.m_Object) { Handle.m_Object=nullptr; }
	~Handle() { HandleClear(&m_Object); }

	// Access
	operator UINT()const { return VariableGet<_ip_t, UINT>(m_Object, 0); }
	_ip_t* operator->()const { return m_Object; }

	// Comparison
	BOOL operator==(UINT Value)const { return VariableEqual(m_Object, Value); }
	BOOL operator!=(UINT Value)const { return !VariableEqual(m_Object, Value); }

	// Assignment
	Handle& operator=(UINT Value) { VariableAssign(&m_Object, Value); return *this; }
	Handle& operator=(_ip_t* Object) { HandleAssign(&m_Object, Object); return *this; }

private:
	// Common
	_ip_t* m_Object;
};
