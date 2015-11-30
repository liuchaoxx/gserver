// gcore.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "design/policy.h"
#include "design/smart_pointer.h"
#include "design/int2type.h"
#include "design/conversion.h"


#include <Windows.h>
#include <iostream>
#include <vector>

int _tmain(int argc, _TCHAR* argv[])
{
// 	WidgetMgr *mgr = new WidgetMgr();
// 	mgr->PrintWedgetInfo ( );
// 	Widget *obj = new Widget();
// 	mgr->SwitchProtoType ( obj );

	
// 	EWNSPtr *eptr = new EWNSPtr ();
// 	WNSPtr* ptr = new WNSPtr ( *eptr );

	using namespace std;
	cout << Conversion<double, int>::exists <<' '
		<< Conversion<char, char*>::exists << ' '
		<<Conversion<size_t, vector<int>>::exists << ' ';


	while (1)
	{
		Sleep ( 10000 );
	}
	return 0;
}

