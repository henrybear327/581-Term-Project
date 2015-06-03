#ifndef GETINPUT
#define GETINPUT

#include <stdio.h>

FILE *get_student_txt_fp();

FILE *get_department_txt_fp();

void show_student_txt(FILE *pFile);

void show_department_txt(FILE *pFile);

#endif