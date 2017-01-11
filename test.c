#include "test.h"

#include <stdio.h>
#include <string.h>

int main()
{
	int ret = 0;
	int i;

	while (test__[i].origin && test__[i].expand && test__[i].match) {
		if (strcmp(test__[i].expand, test__[i].match) == 0) {
			printf("[ok] %s : %s -> %s\n", test__[i].origin, 
			       test__[i].expand, test__[i].match);
		} else {
			printf("[error] %s : %s -> %s\n", test__[i].origin, 
			       test__[i].expand, test__[i].match);
			ret = -1;
		}
		++i;
	}

	if (ret == 0)
		printf("[passed]\n");
	else
		printf("[failed]\n");

	return ret;
}
