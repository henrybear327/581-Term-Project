#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getInput.h"
#include "linkedList.h"
#include "queue.h"
#include "dataType.h"

#define DEBUG 1

int main()
{
    /*
    Rule of thumb

    read information from the text file

    所有學生錄取第一志願
    超額比序，多的進入queue
    */
    FILE *pStudentData = get_student_txt_fp();
    FILE *pDepartmentData = get_department_txt_fp();

#if DEBUG
    show_student_txt(pStudentData);
    show_department_txt(pDepartmentData);
#endif

    // read all student data to queue
    Student *newNode = malloc(sizeof(Student));
    
    
    Student *head, *tail;

    return 0;
}