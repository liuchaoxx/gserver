#ifndef _CONVERSION_H
#define _CONVERSION_H

#include <iostream>
#include <vector>

template<class T, class U>
class Conversion
{
	typedef char Small;
	class Big { char dummy[2]; };
	static Small Test ( U );
	static Big Test ( ... );
	static T MakeT ();
public:
	enum { exists = sizeof( Test ( MakeT () ) )== sizeof( Small ) };
	enum { exists2Way =  exists &&   Conversion<U, T>::exists };
	enum { sameType = false };
};

template<class T>
class Conversion<T, T>
{
public:
	enum { exists = 1, exists2Way = 1, sameType = 1 };
};


#define SUPERSUBCLASS(T, U) \
	( Conversion<const U*, const T*>::exists && \
	!Conversion<const T*, const void*>::sameType )

void test_conversion ()
{
	using namespace std;
	cout << Conversion<double, int>::exists << ' '
		<< Conversion<char, char*>::exists << ' '
		<< Conversion<size_t, vector<int>>::exists << ' '
		<< Conversion<ExtendWidget, Widget>::exists << ' '<<endl;

	cout << SUPERSUBCLASS ( Widget, ExtendWidget ) << ' ' << endl;
	cout << SUPERSUBCLASS ( ExtendWidget, void ) << ' ' << endl;
	cout << SUPERSUBCLASS ( void, ExtendWidget ) << ' ' << endl;
}

#endif