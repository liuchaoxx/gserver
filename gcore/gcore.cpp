// gcore.cpp : �������̨Ӧ�ó������ڵ㡣
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

