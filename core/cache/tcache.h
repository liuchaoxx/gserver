#ifndef _TCACHE_H
#define _TCACHE_H

#include "base_type.h"
#include "sync_lock.h"

#define SET_TCACHE_ID(x, y)	if( (x)!=NULL ) { (x)->SetPoolID( (UINT)y ); }
#define GET_TCACHE_ID(x)	( (x) != NULL ? (x)->GetPoolID() : INVALID_ID ); 
#define RELEASE_TCACHE_OBJ(x) (x)->Release();

class CacheObject
{
public:
	UINT GetCacheID(VOID) const { return m_CacheID; };
	VOID SetCacheID(UINT cid) { this->m_CacheID = cid; }
private:
	UINT m_CacheID;
};

template<typename T> class TCache
{
public:
	TCache( UINT capacity )
	{
		m_obj = new T*[capacity];
		for (INT i = 0; i < capacity; i++){
			m_obj[i] = new T;
			Assert(m_obj[i] == NULL);
		}
		m_pos = 0;
		m_capt = capacity;
	}

	~TCache(VOID)
	{
		if (m_obj != NULL)
		{
			for (INT i = 0; i < m_capt; i++){
				SAFE_DELETE(m_obj[i]);
				m_obj[i] = NULL;
			}
			SAFE_DELETE_ARRAY(m_obj);
		}
		m_capt = 0;
	}

public:
	T*	_Alloc(VOID)
	{
		m_Lock.Lock();
		Assert( m_pos < m_capt);
		if ( m_pos >= m_capt )
		{
			m_Lock.Unlock();
			return NULL;
		}

		T *pObj = m_obj[m_pos];
		SET_TCACHE_ID( pObj, (UINT)m_pos );
		m_pos++;

		m_Lock.Unlock();
		return pObj;
	}

	VOID _Free( T* pObj )
	{
		m_Lock.Lock();
		Assert( pObj != NULL );	
		if ( pObj == NULL )
		{
			m_Lock.Unlock();
			return ;
		}

		Assert( m_pos > 0 );	
		if ( m_pos <= 0 )
		{
			m_Lock.Unlock();
			return ;
		}

		UINT uDelIndex = GET_TCACHE_ID( pObj );
		Assert(uDelIndex < (UINT)m_pos );
		if (uDelIndex >= (UINT)m_pos )
		{
			m_Lock.Unlock();
			return ;
		}

		m_pos--;
		T *pDelObj		= m_obj[uDelIndex];
		m_obj[uDelIndex]= m_obj[m_pos];
		m_obj[m_pos]	= pDelObj;

		SET_TCACHE_ID( m_obj[uDelIndex], uDelIndex );
		SET_TCACHE_ID( m_obj[m_pos], INVALID_ID );

		m_Lock.Unlock();
		return;
	}

	UINT GetCount()
	{
		return m_pos;
	}

private:
	T**  m_obj;
	UINT m_pos;
	SyncLock m_lock;
	UINT m_capt;
};
#endif