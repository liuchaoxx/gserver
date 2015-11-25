#include "stdafx.h"

#include "buffer.h"

Buffer::Buffer( BOOL isRoot /* = false */, UINT vsize /* = -1 */ )
{
	if ( isRoot && vsize > 0 )
	{
		this->m_buf = new CHAR[vsize];
		this->m_len = vsize;
	}
}

VOID Buffer::Init( CHAR* buf, UINT len )
{
	this->m_buf = buf;
	this->m_len = len;
}

BOOL Buffer::Alloc( Buffer *buf )
{
	UINT blen = buf->GetLength();
	UINT remain = m_len - m_tail; 
	if ( blen > remain )
		return FALSE;
	buf->Init( &m_buf[m_tail], blen );
	this->m_tail += blen;
	return TRUE;
}

BOOL Buffer::Free( Buffer *buf )
{
	UINT flen = buf->m_len;
	UINT dlen = m_tail - m_head;
	if ( flen > dlen )
		return FALSE;
	buf->Init( NULL, 0 );
	this->m_head += flen;
	return TRUE;
}

BOOL Buffer::Write ( CHAR* val, UINT len )
{
	UINT remain = m_len - m_tail; 
	if ( len > remain )
		return FALSE;
	memcpy( &( m_buf[m_tail] ), val, len );
	m_tail += len;
	return TRUE;
}

BOOL Buffer::Read ( CHAR* buf, UINT len )
{
	UINT dsize = m_tail - m_head;
	if ( dsize  < len )
		return FALSE;
	memcpy( buf, &(m_buf[m_head]), len );
	m_head += len;
	return TRUE;
}