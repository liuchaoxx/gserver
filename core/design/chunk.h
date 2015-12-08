#ifndef _CHUNK_H
#define _CHUNK_H

#include "assertx.h"
#include <vector>

#define  DEFAULT_CHUNK_SIZE 4096
#define  DEFAULT_SMALLOBJ_SIZE 64

struct Chunk
{
	void Init ( std::size_t blocksize, unsigned char blocks );
	void Release ();
	void* Allocate ( std::size_t blocksize );
	void Deallocate ( void* p, std::size_t blocksize );
	unsigned char* pData_;
	unsigned char firstAvailableBlock_, blocksAvailable_;
};

void Chunk::Init ( std::size_t blocksize, unsigned char blocks )
{
	pData_ = new unsigned char[blocksize * blocks];
	firstAvailableBlock_ = 0; 
	blocksAvailable_ = blocks;
	unsigned char i = 0;
	unsigned char *p = pData_;
	for ( ; i != blocks; p += blocksize )
		*p = ++i;
}

void* Chunk::Allocate ( std::size_t blocksize )
{
	if ( !blocksAvailable_ ) return 0;
	unsigned char* pResult = pData_ + ( firstAvailableBlock_ * blocksize );
	firstAvailableBlock_ = *pResult;
	--blocksAvailable_;
	return pResult;
}

void Chunk::Deallocate ( void* p, std::size_t blocksize )
{
	Assert ( p < pData_ );
	unsigned char* toRelease = static_cast< unsigned char* >( p );
	Assert ( ( toRelease - pData_ ) % blocksize == 0 );
	*toRelease = firstAvailableBlock_;
	firstAvailableBlock_ = static_cast< unsigned char >( ( toRelease - pData_ ) / blocksize );
	Assert ( firstAvailableBlock_ = ( toRelease - pData_ ) / blocksize );
	++blocksAvailable_;
}

class FixedAllocate
{
private:
	std::size_t		blockSize_;
	unsigned char	numBlocks_;
	typedef std::vector<Chunk>	Chunks;
	Chunks chunks_;
	Chunk* allocChunk_;
	Chunk* dealloChunk_;
};

class SmallObjAllocate
{
private:
	std::vector<FixedAllocate> pool_;
	FixedAllocate* pLastAlloc_;
	FixedAllocate* pLastDealloc_;
};


template
<
	template<class T> class ThreadModeling, //= DEFAULR_THREAD_MODEL,
	std::size_t ChunkSize = DEFAULT_CHUNK_SIZE,
	std::size_t MaxSmallObjSize = DEFAULT_SMALLOBJ_SIZE
>
class SmallObject
{
public:
	static void* operator new ( std::size_t size );
	static void operator delete( void* p, std::size_t size );
	virtual ~SmallObject () {}
};


#endif