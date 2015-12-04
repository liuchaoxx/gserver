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
		typedef NullType PointeeType;  //NullType��һ�����ڲ��ܱ�ʹ������µ�ռλ�ͱ�
	};
	template<class U>struct PointerTraits<U*> //����һ��PointerTraits��ƫ�ػ�����һ������κ�ָ���ͱ���ػ��壬�����ָ��ͽ�������ػ���
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