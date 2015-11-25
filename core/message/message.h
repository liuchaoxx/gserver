#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "base_type.h"
#include "buffer.h"
#include <string>
#include <vector>

using namespace std;

class Bean : public Buffer
{
public:
	Bean( Buffer& buf ){};
	~Bean(){};
	virtual BOOL Write(VOID) = 0;
	virtual BOOL Read(VOID) = 0;
};

class Message : public Bean
{
public:
	Message ( Buffer& buf ):Bean ( buf ) {};
	~Message(VOID){};
	vector<ulong>& GetSendID(VOID) const;
	virtual INT GetID(VOID) const = 0;
private:
	vector<ulong> m_SendID;
};

#endif