#ifndef _TRAITS_H
#define _TRAITS_H

#include <vector>
#include <iostream>
#include "null_type.h"
#include "empty_type.h"

using namespace std;

// template <typename T>
// class TypeTraits
// {
// private:
// 	template<class U> struct PointerTraits
// 	{
// 		enum { result = false };
// 		typedef NullType PointeeType;  //NullType��һ�����ڲ��ܱ�ʹ������µ�ռλ�ͱ�
// 	};
// 	template<class U>struct PointerTraits<U*> //����һ��PointerTraits��ƫ�ػ�����һ������κ�ָ���ͱ���ػ��壬�����ָ��ͽ�������ػ���
// 	{
// 		enum { result = true };
// 		typedef U PointeeType;
// 	};
// public:
// 	enum { isPointer = PointerTraits<T>::result };
// 	typedef typename PointerTraits<T>::PointeeType PointeeType;
// };
// 
// 
// template<typename T>
// class TypeTraits_P2M
// {
// private:
// 	template<class U> struct P2MTraits
// 	{
// 		enum { result = false };
// 	};
// 	template<class U, class V> struct P2MTraits<U V::*>
// 	{
// 		enum { result = true };
// 	};
// public:
// 	enum { isMemPointer = P2MTraits<T>::result };
// };
// 
// 
// class A{};
// class B
// {
// public:
// 	A *a;
// };
// 
// void test_traits ()
// {
// 	
// 	cout  << TypeTraits<vector<int>::iterator>::isPointer ? 1 : 2 << '\n';
// 	cout  << TypeTraits<int*>::isPointer ? 1 : 2 << '\n';
// 	cout  << TypeTraits<int>::isPointer ? 1 : 2 << '\n';
// 	cout  << TypeTraits_P2M<A B::*>::isMemPointer ? 1 : 2 << '\n';
// }

// int main ()
// {
// 	test_traits ();
// }
template<bool flag, typename U, typename V>
struct TypeSelect
{
	typedef U Result;
};

template<typename U, typename V>
struct TypeSelect<false, U, V>
{
	typedef V Result;
};

///////////////////////////////////////////////////////////////////////////////////////  
/**
* ������ȡ��, copy�� Loki��
*/
template<typename T>
class TypeTraits
{
private:

	///////////////////////////////////////////////////////  
	//��ȡ���õ�ԭʼ����(��ȥ����������)  
	template<class U>
	struct ReferenceTraits
	{
		enum { result = false };
		typedef U Result;
	};

	template<class U>
	struct ReferenceTraits<U&>
	{
		enum { result = true };
		typedef U Result;
	};

	///////////////////////////////////////////////////////  
	//ָ������  
	template<class U>
	struct PointerTraits
	{
		enum { result = false };
		typedef NullType Result;
	};

	template<class U>
	struct PointerTraits<U*>
	{
		enum { result = true };
		typedef U Result;
	};

	template<class U>
	struct PointerTraits<U*&>
	{
		enum { result = true };
		typedef U Result;
	};

	///////////////////////////////////////////////////////  
	//��Ա����ָ��, gcc ����֧��������, ����֮  
	template<typename U>
	struct PointerToMemberTraits
	{
		enum { result = false };
	};

	template<class U, class V>
	struct PointerToMemberTraits< U V::*>
	{
		enum { result = true };
	};

	template<class U, class V>
	struct PointerToMemberTraits< U V::*&>
	{
		enum { result = true };
	};

	///////////////////////////////////////////////////////  
	// const  
	template<typename U>
	struct UnConstTraits
	{
		enum { result = false };
		typedef U Result;
	};
	template<typename U>
	struct UnConstTraits<const U>
	{
		enum { result = true };
		typedef U Result;
	};
	template<typename U>
	struct UnConstTraits<const U&>
	{
		enum { result = true };
		typedef U& Result;
	};

	///////////////////////////////////////////////////////  
	// volatile  
	template<typename U>
	struct UnVolatileTraits
	{
		enum { result = false };
		typedef U Result;
	};
	template<typename U>
	struct UnVolatileTraits<volatile U>
	{
		enum { result = true };
		typedef U Result;
	};
	template<typename U>
	struct UnVolatileTraits<volatile U&>
	{
		enum { result = true };
		typedef U& Result;
	};
public:
	//T�Ƿ���ָ������  
	enum { isPointer = PointerTraits< T>::result };
	//T�Ƿ�����������  
	enum { isReference = ReferenceTraits<T >::result };
	//T�Ƿ�ָ���Ա������ָ��  
	enum { isMemberPointer = PointerToMemberTraits<T >::result };

	//T�Ƿ���Const����  
	enum { isConst = UnConstTraits< T>::result };
	//T�Ƿ���Volatile����  
	enum { isVolatile = UnVolatileTraits< T>::result };

	//���T��ָ������,���ȡT��ԭ����, ��ȥ��ָ������  
	typedef typename PointerTraits<T>::Result           PointeeType;
	//���T����������,���ȡT��ԭ����, ��ȥ����������  
	typedef typename ReferenceTraits<T>::Result         ReferencedType;
	//���T��Const����,���ȡT��ԭ����, ��ȥ�� Const����  
	typedef typename UnConstTraits<T>::Result           NonConstType;
	//���T��volatile����,���ȡT��ԭ����, ��ȥ��volatile����  
	typedef typename UnVolatileTraits<T>::Result        NonVolatileType;
	//ȥ��const volatile����  
	typedef typename UnVolatileTraits<typename UnConstTraits<T >::Result >::Result UnqualifiedType;

public:

	//���ڸ��������ҷǿ�����, ��ȡ���ݵ���������, ��������������  
	//typedef typename TypeSelect<isBaseType || isNullType, T, ReferencedType&>::Result ReferenceTypeEx;  

	//��ȡ���ݵ�ԭ����, �������õ������������  
	typedef typename TypeSelect<!isReference, T, ReferencedType&>::Result ParameterType;
};
#endif