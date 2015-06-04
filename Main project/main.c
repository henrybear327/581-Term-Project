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
    Student *head = NULL; // head == null --> empty
    head = enqueue_all_student_records(pStudentData);

#if DEBUG
    show_queue(head);

    while (head) {
        printf("Pop a node out from queue\n");
        head = pop(head);
        show_queue(head);
    }
#endif

    // program ending, clean up
    if (fclose(pStudentData) == EOF)
        printf("Error closing pStudentData\n");
    if (fclose(pDepartmentData) == EOF)
        printf("Error closing pDepartmentData\n");

    return 0;
}