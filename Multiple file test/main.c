/*
A simple database system
至少包含Insert, delete, edit, search, write to file, read from file等功能
基本要求: malloc, string, struct, source code in multiple files
查詢和運算功能自己設計，越多越好
參考p. 434但不一定要使用link list
*/

#include <stdio.h>
#include "hello_world.h"

int main()
{
	print_hello_world();
	printf("%d\n", add_integers(1, 2));	
	print_hello_world();
	printf("%d\n", add_integers(4, 2));

	return 0;
}