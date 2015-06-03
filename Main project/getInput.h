#ifndef GETINPUT_H
#define GETINPUT_H

#include <stdio.h>
#include "dataType.h"

/*
Open student.txt and return FILE pointer
*/
FILE *get_student_txt_fp();

/*
Open department.txt and return FILE pointer
*/
FILE *get_department_txt_fp();

/*
Show all data in student.txt
*/
void show_student_txt(FILE *pFile);

/*
Show all data in department.txt
*/
void show_department_txt(FILE *pFile);


#endif