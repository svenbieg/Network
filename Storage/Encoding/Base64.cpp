//============
// Base64.cpp
//============

#include "Base64.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Encoding {


//=======
// Table
//=======

//BASE64    ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/
//Base64Url ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_

const BYTE BASE64[]=
	{
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0x00
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0x10
//                                                           +         -         /
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  62, 255,  62, 255,  63, // 0x20
//    0    1    2    3    4    5    6    7    8    9                   =
	 52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255, 255,   0, 255, 255, // 0x30
//         A    B    C    D    E    F    G    H    I    J    K    L    M    N    O
	255,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14, // 0x40
//    P    Q    R    S    T    U    V    W    X    Y    Z                        _
	 15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255,  63, // 0x50
//         a    b    c    d    e    f    g    h    i    j    k    l    m    n    o
	255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40, // 0x60
//    p    q    r    s    t    u    v    w    x    y    z
	 41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51, 255, 255, 255, 255, 255, // 0x70
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0x80
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0x90
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xA0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xB0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xC0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xD0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xE0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xF0
	};

template <class _char_t> UINT Base64Length(_char_t const* input, UINT& input_size)
{
if(!input)
	return 0;
UINT size=0;
if(input_size==0)
	input_size=-1;
UINT pos=0;
for(; pos<input_size; pos++)
	{
	if(!input[pos])
		break;
	BYTE offset=CharHelper::ToAnsi(input[pos]);
	if(BASE64[offset]!=255)
		size++;
	}
if(input_size==-1)
	input_size=pos;
if(pos==0)
	return 0;
UINT block_size=TypeHelper::AlignUp(size, 4U);
UINT pad=block_size-size;
if(pad>2)
	throw InvalidArgumentException();
UINT len=block_size/4*3-pad;
return len;
}

template <class _char_t> VOID Base64Decode(_char_t const* input, UINT input_size, BYTE* output, UINT output_size)
{
BYTE block[4];
UINT size=0;
UINT pad=0;
auto in=input;
auto in_end=in+input_size;
auto out=output;
auto out_end=out+output_size;
while(out<out_end)
	{
	CHAR c='=';
	if(in<in_end)
		c=CharHelper::ToAnsi(*in++);
	BYTE tmp=BASE64[c];
	if(tmp==255)
		continue;
	if(c=='=')
		pad++;
	block[size]=tmp;
	size++;
	if(size==4)
		{
		*out++=(block[0]<<2)|(block[1]>>4);
		if(pad<2)
			*out++=(block[1]<<4)|(block[2]>>2);
		if(pad<1)
			*out++=(block[2]<<6)|block[3];
		size=0;
		if(pad>0)
			break;
		}
	}
}


//========
// Common
//========

Handle<Buffer> Base64::Decode(LPCSTR input, UINT len)
{
if(!input)
	return nullptr;
UINT size=Base64Length(input, len);
if(!size)
	return nullptr;
auto buf=Buffer::Create(size);
Base64Decode(input, len, buf->Begin(), size);
return buf;
}

Handle<Buffer> Base64::Decode(LPCWSTR input, UINT len)
{
if(!input)
	return nullptr;
UINT size=Base64Length(input, len);
if(!size)
	return nullptr;
auto buf=Buffer::Create(size);
Base64Decode(input, len, buf->Begin(), size);
return buf;
}

UINT Base64::Decode(LPCSTR input, UINT len, BYTE* output, UINT output_size)
{
UINT size=Base64Length(input, len);
if(!size||!output)
	return size;
Base64Decode(input, len, output, size);
return size;
}

Handle<String> Base64::DecodeString(LPCSTR input, UINT len)
{
auto buf=Decode(input, len);
if(!buf)
	return nullptr;
LPCSTR str=(LPCSTR)buf->Begin();
UINT size=buf->GetSize();
return String::Create(size, str);
}

UINT Base64::Encode(VOID const* input, UINT input_size, LPSTR output, UINT output_size)
{
UINT size=input_size*4/3+4;
size+=size/72+1;
if(!output)
	return size;
if(output_size<size)
	return 0;
auto in=(BYTE const*)input;
auto in_end=in+input_size;
auto out=output;
UINT line_len=0;
while(in_end-in>=3)
	{
	*out++=BASE64[in[0]>>2];
	*out++=BASE64[((in[0]&0x03)<<4)|(in[1]>>4)];
	*out++=BASE64[((in[1]&0x0F)<<2)|(in[2]>>6)];
	*out++=BASE64[in[2]&0x3F];
	in+=3;
	line_len+=4;
	if(line_len>=72)
		{
		*out++='\n';
		line_len=0;
		}
	}
if(in<in_end)
	{
	*out++=BASE64[in[0]>>2];
	if(in_end-in==1)
		{
		*out++=BASE64[(in[0]&0x03)<<4];
		*out++='=';
		}
	else
		{
		*out++=BASE64[((in[0]&0x03)<<4)|(in[1]>>4)];
		*out++=BASE64[(in[1]&0x0F)<<2];
		}
	*out++='=';
	line_len+=4;
	if(line_len>=72)
		{
		*out++='\n';
		line_len=0;
		}
	}
*out++=0;
return (UINT)(out-output);
}

}}