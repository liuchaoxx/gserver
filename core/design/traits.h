#ifndef _TRAITS_H
#define _TRAITS_H

#include <vector>
#include <iostream>

using namespace std;

class NullType;

template <typename T>
class TypeTraits
{
private:
	template<class U> struct PointerTraits
	{
		enum { result = false };
		typedef NullType PointeeType;  //NullType是一种用于不能被使用情况下的占位型别
	};
	template<class U>struct PointerTraits<U*> //是上一个PointerTraits的偏特化，是一个针对任何指针型别的特化体，如果是指针就进入这个特化体
	{
		enum { result = true };
		typedef U PointeeType;
	};
public:
	enum { isPointer = PointerTraits<T>::result };
	typedef typename PointerTraits<T>::PointeeType PointeeType;
};


template<typename T>
class TypeTraits_P2M
{
private:
	template<class U> struct P2MTraits
	{
		enum { result = false };
	};
	template<class U, class V> struct P2MTraits<U V::*>
	{
		enum { result = true };
	};
public:
	enum { isMemPointer = P2MTraits<T>::result };
};


class A{};
class B
{
public:
	A *a;
};

void test_traits ()
{
	
	cout  << TypeTraits<vector<int>::iterator>::isPointer ? 1 : 2 << '\n';
	cout  << TypeTraits<int*>::isPointer ? 1 : 2 << '\n';
	cout  << TypeTraits<int>::isPointer ? 1 : 2 << '\n';
	cout  << TypeTraits_P2M<A B::*>::isMemPointer ? 1 : 2 << '\n';
}

// int main ()
// {
// 	test_traits ();
// }

#endif