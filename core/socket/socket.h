#ifndef _SOCKET_H
#define _SOCKET_H

#include "base_type.h"

class IServer;
class ISocket 
{
public:
	ISocket (SOCKET sock, UINT defsbufsize, UINT defrbufsize);
    virtual ~ISocket();
public:
	VOID SetSocketID ( SOCKET sock ) { this->m_SocketID = sock; };
	SOCKET GetSocketID () { return this->m_SocketID; };
	VOID SetSendBuf( CHAR* buf, UINT buf_size ) ;
	VOID SetRecvBuf( CHAR* buf, UINT recv_size ) ;

	UINT Send  (const VOID* buf, UINT len, UINT flags = 0) ;
	UINT Recv (VOID* buf, UINT len, UINT flags = 0);
	BOOL Write(const CHAR* data, const UINT len);
	BOOL Read(CHAR* buf, UINT len);
protected:
	//sock
	SOCKET m_SocketID;
	// socket address structure
	SOCKADDR_IN m_SockAddr;
	// peer host
	CHAR m_Host[IP_SIZE];
	// peer port
	UINT m_Port;
	//data buf
	//cache ID
	UINT m_CacheID;
};

#endif