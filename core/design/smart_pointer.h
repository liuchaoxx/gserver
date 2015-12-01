#ifndef _SMART_POINTER_H
#define _SMART_POINTER_H

#include "policy.h"

template<class T>
class IThreadModel
{
public:
	class Lock
	{
	public:
		Lock ( T& tobj ) {}
	};
};

template<class T>
class SingleThread: public IThreadModel<T> {};

template<class T>
class MutiplyThread : public IThreadModel<T>{};

template<class T>
struct NoChecking
{
	static void Check ( T *obj ) {}
};

template<class T>
struct EnforceNotNull
{
	class NullPointerException: public std::exception {};
	static void Check ( T *obj )
	{
		if ( !obj )
			throw NullPointerException ();
	}
};

template<class T>
struct EnsureNotNull
{
	static void Check ( T*& obj )
	{
		if ( !obj )
			obj = GetDefaultPrinter ();
	}
};

class ExtendWidget : public Widget {};

template<
	class T, 
	template<class> class CheckPolicy,
	template<class> class ThreadPolicy
>
class SmartPointor : public CheckPolicy<T>, public ThreadPolicy<T>
{
public:
	SmartPointor ( ) {}
	template< class T1, template<class> class CP1, template<class> class TP1 >
	SmartPointor ( const SmartPointor<T1, CP1, TP1 >& other ): CheckPolicy<T> ( ( const CheckPolicy<T>& ) other ), ThreadPolicy<T> ( ( const ThreadPolicy<T>& )other )
	{
		this->pointee_ = other.GetPointer();
	}

	T* operator->( )
	{
		typename ThreadPolicy<T>::Lock guard ( *this );
		CheckPolicy<T>::Check ( pointee_ );
		return pointee_;
	}

	T* GetPointer ()const { return pointee_; }
	void SetPointer ( T* ptr ) { this->pointee_ = ptr };
private:
	T* pointee_;
};

typedef SmartPointor<Widget, NoChecking, SingleThread> WNSPtr;
typedef SmartPointor<ExtendWidget, NoChecking, SingleThread> EWNSPtr;

void test_small_pointer ()
{
	EWNSPtr *eptr = new EWNSPtr ();
	WNSPtr* ptr = new WNSPtr ( *eptr );
}

#endif