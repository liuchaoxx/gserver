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

	Functor (){};
	Functor ( const Functor& fun ) { this->spImpl_ = fun.spImpl_; };
	explicit Functor ( std::auto_ptr<Impl> spImpl ):spImpl_ ( spImpl ) {}
	template<class Fun> Functor ( const Fun& fun ):spImpl_ ( new FunctorHandler<Functor, Fun> ( fun ) ) {}

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
	: public FunctorImpl< typename ParentFunctor::ResultType, typename ParentFunctor::ParamList >
{
public:
	typedef typename ParentFunctor::ResultType ResultType;
	FunctorHandler ( const Fun& fun ): fun_( fun ) {}

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

void test_functor_main ()
{
// 	TestFunctor f;
// 	Functor<void, TYPELIST_2 ( int, double )> cmdf ( f );
// 	cmdf ( 4, 4.5 );

	Functor<void, TYPELIST_2 ( int, double )> cmdf1 ( test_function );
	cmdf1 ( 4, 4.5 );
}
#endif