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
    Student *student_head = NULL; // head == null --> empty
    student_head = enqueue_all_student_records(pStudentData);

#if DEBUG
    show_queue(student_head);

    while (student_head) {
        printf("Pop a node out from queue\n");
        student_head = pop(student_head);
        show_queue(student_head);
    }
#endif

    // read all data from department.txt
    Department *department_head = load_department_data(pDepartmentData);

#if DEBUG
    show_all_node(department_head);
#endif

    // program ending, clean up
    if (fclose(pStudentData) == EOF)
        printf("Error closing pStudentData\n");
    if (fclose(pDepartmentData) == EOF)
        printf("Error closing pDepartmentData\n");

    return 0;
}