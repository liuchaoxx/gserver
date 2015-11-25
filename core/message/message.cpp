#include "message.h"
// 
// BOOL Bean::WriteByte ( const CHAR* val, UINT len )
// {
// 	UINT remain = m_len -  m_tail;
// 	if ( remain < len )
// 		return FALSE;
// 
// 	memcpy( &( m_buf[m_tail] ), val, len );
// 	m_tail += len;
// 	return TRUE;
// }
// 
// BOOL Bean::ReadByte ( CHAR* buf, UINT len )
// {
// 	UINT dsize = m_tail - m_head;
// 	if ( dsize  < len )
// 		return FALSE;
// 
// 	memcpy( buf, &(m_buf[m_head]), len );
// 	m_head += len;
// 	return TRUE;
// }
// 
// BOOL Bean::WriteStr ( const string& val )
// {
// 	INT len = strlen ( val.c_str () );
// 	WriteByte ( ( CHAR* )&len, sizeof( INT ) );
// 	WriteByte ( ( CHAR* )val.c_str (), len );
// 	return TRUE;
// }
// 
// BOOL Bean::ReadStr ( string& val )
// {
// 	INT len = 0;
// 	ReadByte ( ( CHAR* )&len, sizeof( INT ) );
// 	val.resize ( len );
// 	ReadByte ( ( CHAR* )val.c_str (), len );
// 	return TRUE;
// }
// 
// BOOL Bean::ReadBean ( Bean& val )
// {
// 	return val.Read ();
// }
// 
// BOOL Bean::WriteBean ( Bean& val )
// {
// 	UINT dlen = val.GetLength()();
// 
// 	val.Init(m)
// 	return val.Write ();
// }
// 
