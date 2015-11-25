#ifndef _BUFFER_H
#define _BUFFER_H

#include "assertx.h"
#include "base_type.h"

class Buffer
{
public:
	Buffer( BOOL isRoot = false, UINT vsize = -1 ):m_buf(NULL), m_len(0), m_head(0), m_tail(0);
	~Buffer(VOID) {};
public:
	VOID Init( CHAR* buf, UINT len );
	BOOL Alloc( Buffer *buf );
	BOOL Free( Buffer *buf );
	BOOL Write ( CHAR* val, UINT len );
	BOOL Read ( CHAR* buf, UINT len );
	virtual UINT GetLength(VOID) const { return 0; };
private:
	CHAR *m_buf;
	UINT m_len;
	UINT m_head;
	UINT m_tail;
};

#endif