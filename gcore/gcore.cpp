// gcore.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "design/policy.h"
#include "design/smart_pointer.h"
#include "design/int2type.h"
#include "design/conversion.h"


#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	test_policy ();
	test_small_pointer ();
	test_conversion ();

	while (1)
	{
		Sleep ( 10000 );
	}
	return 0;
}

