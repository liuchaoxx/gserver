#ifndef _GEN_HIERARCHY_H
#define _GEN_HIERARCHY_H

#include "type_list.h"
#include <string>
using namespace std;

template<class TList, template<class> class Unit>
class GenScatterHierarchy;

template<class T1, class T2, template<class> class Unit>
class GenScatterHierarchy<TypeList<T1, T2>, Unit>
	: public GenScatterHierarchy<T1, Unit>
	, public GenScatterHierarchy<T2, Unit>
{};

template<template<class> class Unit>
class GenScatterHierarchy<NullType, Unit> {};

template<class T>
struct Holder
{
	T value_;
};

typedef GenScatterHierarchy<TYPELIST_3 ( int, string, Widget ), Holder> WidgetInfo;


template<class T, class TList, template<class> class Unit>
Unit<T>& Field(GenScatterHierarchy<TList, Unit>& obj)
{
	return obj;
}

template<class TList, template<class> class Unit>
Unit<typename TList::Head> FieldHelper ( GenScatterHierarchy<TList, Unit>& obj, Int2Type<0> )
{
	GenScatterHierarchy<TList::Head, Unit>& rightBase = obj;
	return rightBase;
}

template<int index, class TList, template<class> class Unit>
Unit<TypeAt<TList, index>> FieldHelper ( GenScatterHierarchy<TList, Unit>& obj, Int2Type<index> )
{
	GenScatterHierarchy<typename TList::Tail, Unit>& rightBase = obj;
	return rightBase;
}

template<int index, class TList, template<class> class Unit>
Unit<TypeAt<TList, index>> Field( GenScatterHierarchy<TList, Unit>& obj )
{
	return FieldHelper(obj, Int2Type<index>);
}

#endif