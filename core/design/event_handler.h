#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

#include "type_list.h"
#include "empty_type.h"

template<class T, class Base>
class EventHandler: public Base
{
public:
	virtual void OnEnent ( T&, int eventId ) = 0;
};

template<
	class TList, 
	template<class AtomicType, class Base> class Unit, 
	class Root = EmptyType 
>
class GenLinearHierarchy;

template<
	class T1, 
	class T2, 
	template<class AtomicType, class Base> class Unit, 
	class Root
>
class GenLinearHierarchy<TypeList<T1, T2>, Unit, Root> 
	: public Unit<T1, GenLinearHierarchy<T2, Unit, Root>>{};

template<
	class T,
	template<class AtomicType, class Base> class Unit,
	class Root
>
class GenLinearHierarchy<TYPELIST_1(T), Unit, Root> 
	: public Unit<T, Root> {};


typedef GenLinearHierarchy<
	TYPELIST_3(int, char, long),
	EventHandler
>	
MyEnterHandler;
#endif