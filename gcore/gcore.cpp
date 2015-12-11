// gcore.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "design/policy.h"
#include "design/smart_pointer.h"
#include "design/int2type.h"
#include "design/conversion.h"
#include "design/traits.h"
#include "design/type_list.h"
#include "design/gen_hierarchy.h"
#include "design/event_handler.h"
#include "design/chunk.h"
#include "design/functor.h"

#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
// 	test_policy ();
// 	test_small_pointer ();
// 	test_conversion ();
//	test_traits ();
//	test_type_list ();
	test_functor_main ();


	while (1)
	{
		Sleep ( 10000 );
	}
	return 0;
}

