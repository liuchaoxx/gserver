#ifndef _SMART_POINTER_H
#define _SMART_POINTER_H

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

template<
	class T, 
	template<class> class CheckPolicy, 
	template<class> class ThreadPolicy
>
class SmartPointor : public CheckPolicy<T>, public ThreadPolicy<T>
{
public:
	T* operator->( )
	{
		typename ThreadPolicy<T>::Lock guard ( *this );
		CheckPolicy<T>::Check ( pointee_ );
		return pointee_;
	}
private:
	T* pointee_;
};



#endif