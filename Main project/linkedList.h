#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include "dataType.h"
/*
Load all data from department.txt
*/
Department *load_department_data(FILE *pFile);

void show_all_node(Department *head);

void search_node(char dataType, void *head, long long int);

void edit_department_data(Department *head, long long int);

#endif