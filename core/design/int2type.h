#ifndef _INT2TYPE_H
#define _INT2TYPE_H

#include <string>


using namespace std;

template<int v>
struct Int2Type
{
	enum { value = v };
};


template<class T, bool isPloyMorphic>
class NiftyContainer
{
private:
	void DoSomething ( T* obj, Int2Type<false> )
	{
	}

	void DoSomething ( T* obj, Int2Type<true> )
	{

	}

public:
	void DoSomething ( T* obj )
	{
		DoSomething ( obj, Int2Type<isPloyMorphic> () );
	}
};


template<typename T>
struct Type2Type
{
	typedef T OriginalType;
};

template<class T, class U>
T* Create ( const U& argv, Type2Type<T> )
{
	return new T ( argv );
}

template<class U>
Widget* Create ( const U& argv, Type2Type<Widget> )
{
	return new Widget ( argv, -1 );
}

string *str = Create ( "hello", Type2Type<string> () );
Widget *wdg= Create ( 100, Type2Type<Widget> ( ) );


template<bool flag, typename T, typename U>
struct Select
{
	typedef T Result;
};

template<typename T, typename U>
struct Select<false, T, U>
{
	typedef U Result;
};


template<class T, bool isPloyMorphic>
class LNiftyContainer
{
	typedef Select<isPloyMorphic, T, T*> ValueType;
};

#endif