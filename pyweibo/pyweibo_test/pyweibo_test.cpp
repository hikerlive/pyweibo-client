// pyweibo_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pyweibo.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	ret = login("13581877736", "E10ADC3949BA59ABBE56E057F20F883E");
	return 0;
}

