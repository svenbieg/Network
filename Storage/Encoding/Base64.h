//==========
// Base64.h
//==========

#pragma once


//=======
// Using
//=======

#include "Storage/Buffer.h"
#include "StringClass.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Encoding {


//========
// Base64
//========

class Base64
{
public:
	// Common
	static Handle<Buffer> Decode(LPCSTR Input, UINT Length);
	static Handle<Buffer> Decode(LPCWSTR Input, UINT Length);
	static UINT Decode(LPCSTR Input, UINT InputSize, BYTE* Output, UINT OutputSize);
	static Handle<String> DecodeString(LPCSTR Input, UINT Length);
	static UINT Encode(VOID const* Input, UINT InputSize, LPSTR Output, UINT OutputSize);
};

}}