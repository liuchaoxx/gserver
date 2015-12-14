#ifndef _FUNCTOR_H
#define _FUNCTOR_H

#include "null_type.h"
#include "type_list.h"
#include <iostream>

//--------------------------------------------
//functor_inpl
template<typename R, class TList>
class FunctorImpl;

template<typename R>
class FunctorImpl<R, NullType>
{
public:
	virtual R operator() ( ) = 0;
	virtual FunctorImpl* Clone () const = 0;
	virtual ~FunctorImpl( ) {};
};

template<typename R, typename P1>
class FunctorImpl<R, TYPELIST_1 ( P1 )>
{
public:
	virtual R operator() ( P1 ) = 0;
	virtual FunctorImpl* Clone () const = 0;
	virtual ~FunctorImpl () {};
};

template<typename R, typename P1, typename P2>
class FunctorImpl<R, TYPELIST_2 ( P1, P2 )>
{
public:
	virtual R operator() ( P1, P2 ) = 0;
	virtual FunctorImpl* Clone () const = 0;
	virtual ~FunctorImpl () {};
};

//--------------------------------------------
//functor
template<typename R, class TList>
class Functor
{
public:
	typedef typename R ResultType;
	typedef FunctorImpl<R, TList> Impl;
	typedef TList ParamList;
	typedef typename TypeAt<TList, 0>::Result Param1;
	typedef typename TypeAt<TList, 1>::Result Param2;

	Functor ()
	{
	}

	Functor ( const Functor& fun ) 
	{ 
		this->spImpl_ = fun.spImpl_; 
	}

	explicit Functor ( std::auto_ptr<Impl> spImpl ):spImpl_ ( spImpl ) 
	{
	}

	template<typename Fun>
	Functor ( const Fun& fun )
		:spImpl_ ( new FunctorHandler<Functor, Fun> ( fun ) ) 
	{
	}

	template<typename PointerToObj, typename PointerToMemFun> 
	Functor ( const PointerToObj& pObj, PointerToMemFun pMemFun ) 
		: spImpl_ ( new MemFunctorHandler<Functor, PointerToObj, PointerToMemFun> ( pObj, pMemFun ) ) 
	{
	}

	Functor& operator =( const Functor& fun ) 
	{
		if ( *this == fun )
			return *this;
		this->spImpl_ = fun.spImpl_;
		return *this;
	}
	
	R operator()()
	{
		return ( *spImpl_ )( );
	}

	R operator()( Param1 p1 )
	{
		return ( *spImpl_ )( p1 );
	}

	R operator()( Param1 p1, Param2 p2 ) 
	{
		return ( *spImpl_ )( p1, p2 );
	}

private:
	std::auto_ptr<Impl> spImpl_;
};

//--------------------------------------------
//functor_handler
template<class ParentFunctor, typename Fun>
class FunctorHandler  
	: public FunctorImpl
	<
		typename ParentFunctor::ResultType,
		typename ParentFunctor::ParamList
	>
{
public:
	typedef typename ParentFunctor::ResultType ResultType;

	FunctorHandler ( const Fun& fun ): fun_( fun ) 
	{
	}

	FunctorHandler* Clone() const
	{
		return new FunctorHandler ( *this );
	}

	ResultType operator()() 
	{
		return fun_();
	}

	ResultType operator()( typename ParentFunctor::Param1 p1 )
	{
		return fun_ ( p1 );
	}

	ResultType operator()( typename ParentFunctor::Param1 p1, typename ParentFunctor::Param2 p2 )
	{
		return fun_ ( p1, p2 );
	}
private:
	Fun fun_;
};

//--------------------------------------------
//Mem functor_handler
template<class ParentFunctor, typename PointerToObj, typename PointerToMemFun>
class MemFunctorHandler
	: public FunctorImpl
	<
		typename ParentFunctor::ResultType, 
		typename ParentFunctor::ParamList 
	>
{
public:
	typedef typename ParentFunctor::ResultType ResultType;

	MemFunctorHandler ( const PointerToObj& pObj, PointerToMemFun pMemFun )
		: pObj_ ( pObj ), pMemFun_ ( pMemFun ) 
	{
	}

	MemFunctorHandler * Clone ( ) const
	{
		return new MemFunctorHandler ( *this );
	}

	ResultType operator()()
	{
		return ( ( *pObj_ ).*pMemFun_ )( );
	}

	ResultType operator()( typename ParentFunctor::Param1 p1 )
	{
		return ( ( *pObj_ ).*pMemFun_ )( p1 );
	}

	ResultType operator()( typename ParentFunctor::Param1 p1, typename ParentFunctor::Param2 p2 )
	{
		return ( ( *pObj_ ).*pMemFun_ )( p1, p2 );
	}
private:
	PointerToObj pObj_;
	PointerToMemFun pMemFun_;
};

//--------------------------------------------
//bind first
template<class Incoming>
class BindFirst
	:public FunctorImpl
	<
		typename Incoming::ResultType,
		typename Incoming::Arguments::Tail
	>
{
public:
	typedef Functor<typename Incoming::ResultType, typename Incoming::Arguments::Tail> Outgoing;
	typedef typename Incoming::Arguments::Param1 Bound;
	typedef typename Incoming::ResultType ResultType;

	BindFirst ( const Incoming& fun, Bound bound )
		: fun_ ( fun ), bound_ ( bound )
	{
	}

	ResultType operator()
	{
		return fun_ ( bound )l
	}

	ResultType operator( typename Outgoing::Param1 p1 )
	{
		return fun_ ( bound, p1 );
	}

	ResultType operator( typename Outgoing::Param1 p1, typename Outgoing::Param1 p2 )
	{
		return fun_ ( bound, p1, p2 );
	}
private:
	Incoming fun_;
	Bound bound_;
};

template<typename T>
class BindFirstTraits
{
private:
	template<class U> struct BoundFunctorTraits
	{
		typedef NullType BoundFunctorType;
	};

	template<class U, class V> struct BoundFunctorTraits<U V::*>
	{
		typedef typename U V::* BoundFunctorType;
	};
public:
	typedef typename BoundFunctorTraits<T>::BoundFunctorType BoundFunctorType;
};


using namespace std;

struct TestFunctor 
{
	void operator() ( int i, double d ) 
	{
		cout << "testfunctor::operator()(" << i << " , " << d << ") called. \n";
	}
};

void test_function ( int i, double d )
{
	cout << "test_function(" << i << " , " << d << ") called. \n";
}
const char* test_function_retvalue ( double, double )
{
	static const char buffer[] = "hello world";
	return buffer;
}


class MyStar
{
public:
	void Show ( int, int )
	{
		cout << "look up, how many star, my star" << endl;
	}
	void Hide ( int, int )
	{
		cout << "hi, it is time that i disappear" << endl;
	}
};


void test_functor_main ()
{
// 	TestFunctor f;
// 	Functor<void, TYPELIST_2 ( int, double )> cmdf ( f );
// 	cmdf ( 4, 4.5 );

// 	Functor<void, TYPELIST_2 ( int, double )> cmdf1 ( &test_function );
// 	cmdf1 ( 4, 4.5 );

// 	Functor<string, TYPELIST_2 ( int, int )> cmd2 ( &test_function_retvalue );
// 	cout << cmd2 ( 10, 10 ).substr ( 7 );

	MyStar star;
	Functor<void, TYPELIST_2 ( int, int )> cmd1 ( &star, &MyStar::Show );
	Functor<void, TYPELIST_2 ( int, int )> cmd2 ( &star, &MyStar::Hide );
	cmd1 ( 10, 10 );
	cmd2 ( 10, 10 );
}

#endif