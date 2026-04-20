//=========
// Email.h
//=========

#pragma once


//=======
// Using
//=======

#include "Concurrency/Task.h"
#include "Storage/Streams/InputStream.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Smtp {


//========
// E-Mail
//========

class Email: public Object
{
public:
	// Using
	using InputStream=Storage::Streams::InputStream;
	using Task=Concurrency::Task;

	// Con-/Destructors
	static inline Handle<Email> Create() { return new Email(); }

	// Common
	Handle<String> From;
	VOID Send(Handle<String> Server, Handle<String> User, Handle<String> Password);
	Handle<String> Subject;
	Handle<String> Text;
	Handle<String> To;

private:
	// Con-/Destructors
	Email()=default;

	// Common
	INT ReadStatus(InputStream* Stream, LPSTR Buffer, UINT BufferSize);
	VOID ThrowIfFailed(INT Status, INT Min, INT Max);
};

}}