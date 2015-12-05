#ifndef _TYPE_LIST_H
#define _TYPE_LIST_H

#include "type_list.h"
#include <iostream>
#include "conversion.h"

template< class T, class U >
struct TypeList
{
	typedef T head;
	typedef U tail;
};

//define
#define TYPELIST_1(T1) TypeList<T1, NullType>
#define TYPELIST_2(T1, T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) TypeList<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) TypeList<T1, TYPELIST_3(T2, T3, T4)>
#define TYPELIST_5(T1, T2, T3, T4, T5) TypeList<T1, TYPELIST_4(T2, T3, T4, T5)>


//---------------------------------------------------------
//计算长度
template< class TList> struct Length;

template<> struct Length<NullType>
{
	enum { value = 0 };
};

template<class T, class U>
struct Length<TypeList<T, U>>
{
	enum { value = 1 + Length<U>::value };
};

//----------------------------------------------------------
//索引式访问
template<class TList, unsigned int index> struct TypeAt;

template<class Head, class Tail> 
struct TypeAt<TypeList<Head, Tail>, 0>
{
	typedef Head Result;
};

template<class Head, class Tail, unsigned int index> 
struct TypeAt<TypeList<Head, Tail>, index>
{
	typedef typename TypeAt<Tail, index-1>::Result Result;
};

//----------------------------------------------------------
//查找typelist
template<class TList, class T> struct IndexOf;

template<class T> 
struct IndexOf<NullType, T>
{
	enum { value = -1 };
};

template<class Tail, class T> 
struct IndexOf<TypeList<T, Tail>, T>
{
	enum { value = 0 };
};

template<class Head, class Tail, class T>
struct IndexOf<TypeList<Head, Tail>, T>
{
private:
	enum { temp = IndexOf<Tail, T>::value };
public:
	enum { value = temp == -1 ? -1 : 1 + temp };
};

//----------------------------------------------------------
//附加元素
template<class TList, class T> struct Append;

template<> 
struct Append<NullType, NullType>
{
	typedef NullType Result;
};

template<class T> 
struct Append<NullType, T>
{
	typedef  TYPELIST_1(T) Result;
};

template<class Head, class Tail> 
struct Append<NullType, TypeList<Head, Tail>>
{
	typedef TypeList<Head, Tail> Result;
};

template<class Head, class Tail, class T>
struct Append<TypeList<Head, Tail>, T>
{
	typedef TypeList<Head, typename Append<Tail, T>::Result> Result;
};


//------------------------------------------------------
//移除第一个
template<class TList, class T> struct Erase;

template<class T>
struct Erase<NullType, T>
{
	typedef  NullType Result;
};

template<class Tail, class T>
struct Erase<TypeList<T, Tail>, T>
{
	typedef Tail Result;
};

template<class Head, class Tail, class T>
struct Erase<TypeList<Head, Tail>, T>
{
	typedef  TypeList<Head, typename Erase<Tail, T>::Result> Result;
};

//------------------------------------------------------
//移除所有
template<class TList, class T> struct EraseAll;

template<class T>
struct EraseAll<NullType, T>
{
	typedef  NullType Result;
};

template<class Tail, class T>
struct EraseAll<TypeList<T, Tail>, T>
{
	typedef typename EraseAll<Tail, T>::Result Result;
};

template<class Head, class Tail, class T>
struct EraseAll<TypeList<Head, Tail>, T>
{
	typedef  TypeList<Head, typename EraseAll<Tail, T>::Result> Result;
};

//------------------------------------------------------
//移除重复元素
template<class TList> struct EraseDuplicates;

template<>
struct EraseDuplicates<NullType>
{
	typedef  NullType Result;
};

template<class Head, class Tail>
struct EraseDuplicates<TypeList<Head, Tail>>
{
private:
	typedef  typename EraseDuplicates<Tail>::Result L1;
	typedef  typename Erase<Tail, Head>::Result L2;
public:
	typedef  TypeList<Head, L2> Result;
};

//------------------------------------------------------
//取代某元素
template<class TList, class T, class U> struct Replace;

template<class T, class U>
struct Replace<NullType, T, U>
{
	typedef  NullType Result;
};

template<class Tail, class T, class U>
struct Replace<TypeList<T, Tail>, T, U>
{
	typedef TypeList<U, Tail> Result;
};

template<class Head, class Tail, class T, class U> 
struct Replace<TypeList<Head, Tail>, T, U>
{
	typedef TypeList<Head, typename Replace<Tail, T, U>::Result> Result;
};

void test_type_list ()
{
	using namespace std;
	cout << "Length == " << Length<TYPELIST_2(int, int)>::value << "\n";
	cout << "Length == " << Length<TYPELIST_3 ( int, int, int )>::value << "\n";
	cout << "Length == " << Length<TYPELIST_4 ( int, int, int, int )>::value << "\n";
	cout << "Length == " << Length<TYPELIST_5 ( int, int, int, int, int )>::value << "\n";

	cout << "TypeAt == " << Conversion<int, TypeAt<TYPELIST_3 ( int, char, short), 0>::Result>::sameType << "\n";
	cout << "TypeAt== " << Conversion<int, TypeAt<TYPELIST_3 ( int, char, short ), 1>::Result>::sameType << "\n";
	cout << "TypeAt== " << Conversion<int, TypeAt<TYPELIST_3 ( int, char, short ), 2>::Result>::sameType << "\n";

	cout << "IndexOf == " << IndexOf<TYPELIST_3 ( int, char, short ), int>::value << "\n";
	cout << "IndexOf == " << IndexOf<TYPELIST_3 ( int, char, short ), char>::value << "\n";
	cout << "index == " << IndexOf<TYPELIST_3 ( int, char, short ), short>::value << "\n";
	cout << "IndexOf == " << IndexOf<TYPELIST_3 ( int, char, short ), long>::value << "\n";

	cout << "Append == " << Length<Append<TYPELIST_1 ( int ), char>::Result>::value << "\n";
	cout << "Append == " << Length<Append<TYPELIST_2 ( int, char), short>::Result>::value << "\n";

	cout << "Erase == " << Length<Erase<TYPELIST_4 ( int, char, short, long ), long>::Result>::value << "\n";
	cout << "Erase == " << Length<Erase<TYPELIST_3 ( int, char, short ), long>::Result>::value << "\n";

	cout << "EraseAll == " << Length<EraseAll<TYPELIST_4 ( int, long, short, long ), long>::Result>::value << "\n";
	cout << "EraseAll == " << Length<EraseAll<TYPELIST_3 ( short, char, short ), short>::Result>::value << "\n";

	cout << "EraseDuplicates == " << Length<EraseDuplicates<TYPELIST_3 ( long, short, char, short, long )>::Result>::value << "\n";
	cout << "EraseDuplicates == " << Length<EraseDuplicates<TYPELIST_3 ( int, char, short )>::Result>::value << "\n";
	cout << "EraseDuplicates == " << Length<EraseDuplicates<TYPELIST_3 ( short, char, short )>::Result>::value << "\n";

	cout << "Replace == " << Conversion<long, TypeAt<Replace<TYPELIST_3 ( int, char, short ), char, long>::Result, 1>::Result>::sameType << "\n";
	cout << "Replace == " << Conversion<char, TypeAt<Replace<TYPELIST_3 ( int, char, short ), char, long>::Result, 1>::Result>::sameType << "\n";
}
#endif