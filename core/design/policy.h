#ifndef _POLICY_H
#define _POLICY_H

using namespace std;

template<class T>
struct OptNewCreator
{ 
	static T* Create ()
	{
		return new T;
	}
protected:
	~OptNewCreator ( ) {};
};

template<class T>
struct OptMallocCreator
{
	static T* Create ()
	{
		void *buf = malloc ( sizeof( T ));
		if ( !buf )
			return 0;
		return new( buf )T;
	}
protected:
	~OptMallocCreator ( ) {};
};

template<class T>
struct OptCloneCreator
{
	OptCloneCreator ( T* pptype = 0 ):pPrototype ( pptype ) {};

	T* Create ()
	{
		return pPrototype ? pPrototype->Clone () : 0;
	}

	void SetProtoType ( T* pptype )
	{
		this->pPrototype = pptype;
	}

	T* GetProtoType () const
	{
		return this->pPrototype;
	}
private:
	T* pPrototype;
protected:
	~OptCloneCreator () {};
};

class Widget
{
public:
	Widget ( int count_, int flag ) {}
	int count_;
	Widget* Clone ()
	{
		return NULL;
	}
};

template< template< class Created > class CreationPolicy >
class WidgetManager: public CreationPolicy< Widget >
{
public:
	void PrintWedgetInfo ()
	{
		Widget* obj = this->Create ( );
	}

	void SwitchProtoType ( Widget *obj )
	{
		CreationPolicy<Widget>& policy = *this;
		delete policy.GetProtoType ();
		policy.SetProtoType ( obj );
	}
};

typedef WidgetManager<OptCloneCreator> WidgetMgr;

#endif