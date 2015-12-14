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
// 		typedef NullType PointeeType;  //NullType是一种用于不能被使用情况下的占位型别
// 	};
// 	template<class U>struct PointerTraits<U*> //是上一个PointerTraits的偏特化，是一个针对任何指针型别的特化体，如果是指针就进入这个特化体
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
* 类型萃取器, copy至 Loki库
*/
template<typename T>
class TypeTraits
{
private:

	///////////////////////////////////////////////////////  
	//提取引用的原始类型(即去掉引用类型)  
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
	//指针类型  
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
	//成员函数指针, gcc 下面支持有问题, 屏蔽之  
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
	//T是否是指针类型  
	enum { isPointer = PointerTraits< T>::result };
	//T是否是引用类型  
	enum { isReference = ReferenceTraits<T >::result };
	//T是否指向成员函数的指针  
	enum { isMemberPointer = PointerToMemberTraits<T >::result };

	//T是否是Const类型  
	enum { isConst = UnConstTraits< T>::result };
	//T是否是Volatile类型  
	enum { isVolatile = UnVolatileTraits< T>::result };

	//如果T是指针类型,则获取T的原类型, 即去掉指针类型  
	typedef typename PointerTraits<T>::Result           PointeeType;
	//如果T是引用类型,则获取T的原类型, 即去掉引用类型  
	typedef typename ReferenceTraits<T>::Result         ReferencedType;
	//如果T是Const类型,则获取T的原类型, 即去掉 Const类型  
	typedef typename UnConstTraits<T>::Result           NonConstType;
	//如果T是volatile类型,则获取T的原类型, 即去掉volatile类型  
	typedef typename UnVolatileTraits<T>::Result        NonVolatileType;
	//去掉const volatile类型  
	typedef typename UnVolatileTraits<typename UnConstTraits<T >::Result >::Result UnqualifiedType;

public:

	//对于复杂类型且非空类型, 获取数据的引用类型, 即加上引用类型  
	//typedef typename TypeSelect<isBaseType || isNullType, T, ReferencedType&>::Result ReferenceTypeEx;  

	//获取数据的原类型, 消除引用的引用这种情况  
	typedef typename TypeSelect<!isReference, T, ReferencedType&>::Result ParameterType;
};
#endif