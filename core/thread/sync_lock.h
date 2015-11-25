#ifndef _CORE_LOCK_H
#define _CORE_LOCK_H

#include "pthread.h"
#include "base_type.h"

class SyncLock
{
	pthread_mutex_t 	m_Mutex; 
public :
	SyncLock( ){ pthread_mutex_init( &m_Mutex , NULL );} ;
	~SyncLock( ){ pthread_mutex_destroy( &m_Mutex) ; } ;
	VOID	Lock( ){ pthread_mutex_lock(&m_Mutex); } ;
	VOID	Unlock( ){ pthread_mutex_unlock(&m_Mutex); } ;
};

#endif