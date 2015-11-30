#ifndef _CONVERSION_H
#define _CONVERSION_H

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
};

#endif