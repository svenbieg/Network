//===========
// Email.cpp
//===========

#include "Email.h"


//=======
// Using
//=======

#include "Concurrency/Task.h"
#include "Network/Tls/TlsClient.h"
#include "Storage/Encoding/Base64.h"
#include "Storage/Streams/StreamWriter.h"
#include "Storage/Buffer.h"

using namespace Concurrency;
using namespace Network::Tls;
using namespace Storage;
using namespace Storage::Encoding;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Smtp {


//==========
// Settings
//==========

constexpr WORD SNTP_PORT=587;


//========
// Common
//========

VOID Email::Send(Handle<String> server, Handle<String> user, Handle<String> password)
{
auto tls_con=TlsClient::Connect(server, SNTP_PORT);
UINT buf_size=512;
auto buf=Buffer::Create(buf_size);
LPSTR str=(LPSTR)buf->Begin();
INT status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 200, 300);
StreamWriter writer(tls_con);
writer.Print("EHLO email\r\n");
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 200, 300);
writer.Print("STARTTLS\r\n");
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 200, 300);
tls_con->Handshake();
writer.Print("EHLO email\r\n");
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 200, 300);
writer.Print("AUTH LOGIN\r\n");
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 300, 400);
Base64::Encode(user->Begin(), user->GetLength(), str, buf_size);
writer.Print(str);
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 300, 400);
Base64::Encode(password->Begin(), password->GetLength(), str, buf_size);
writer.Print(str);
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 200, 300);
writer.Print("MAIL FROM:<");
writer.Print(From);
writer.Print(">\r\n");
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 200, 300);
writer.Print("RCPT TO:<");
writer.Print(To);
writer.Print(">\r\n");
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 200, 300);
writer.Print("DATA\r\n");
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 300, 400);
writer.Print("From: ");
writer.Print(From);
writer.Print("\r\nSubject: ");
writer.Print(Subject);
writer.Print("\r\nTo: ");
writer.Print(To);
writer.Print("\r\n\r\n");
writer.Print(Text);
writer.Print("\r\n.\r\n");
tls_con->Flush();
status=ReadStatus(tls_con, str, buf_size);
ThrowIfFailed(status, 200, 300);
}


//================
// Common Private
//================

INT Email::ReadStatus(InputStream* stream, LPSTR buf, UINT size)
{
SIZE_T read=stream->Read(buf, size);
buf[read]=0;
INT status=0;
StringHelper::Scan(buf, "%i", &status);
return status;
}

VOID Email::ThrowIfFailed(INT status, INT min, INT max)
{
if(status>=min&&status<max)
	return;
throw InvalidArgumentException();
}

}}