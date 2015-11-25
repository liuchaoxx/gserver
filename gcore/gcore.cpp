// gcore.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "design/policy.h"
#include "design/smart_pointer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	WidgetMgr *mgr = new WidgetMgr();
	mgr->PrintWedgetInfo ( );
	Widget *obj = new Widget();
	mgr->SwitchProtoType ( obj );
	return 0;
}

