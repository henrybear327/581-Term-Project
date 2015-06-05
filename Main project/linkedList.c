#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"

Department *load_department_data(FILE *pFile)
{
    rewind(pFile);

    Department *head = NULL;
    Department *prev = NULL;
    while (1) {
        if (head == NULL) {
            if ((head = calloc(1, sizeof(Department))) == NULL) {
                CALLOC_ERROR;
                exit(0);
            }
            if (fscanf(pFile, "%lld %s %d", &head->ID, head->name, &head->quota) ==
                EOF)
                break;

            prev = head;
            head->next = NULL;
            head->department_student_head = NULL;
        } else {
            Department *new;
            if ((new = calloc(1, sizeof(Department))) == NULL) {
                CALLOC_ERROR;
                exit(0);
            }
            if (fscanf(pFile, "%lld %s %d", &new->ID, new->name, &new->quota) == EOF)
                break;
            prev->next = new;

            prev = new;
            new->next = NULL;
            new->department_student_head = NULL;
        }
    }

    rewind(pFile);
    return head;
}

void show_all_node(Department *head)
{
    printf("---Showing all node---\n");
    while (head) {
        printf("%lld %s %d %p %p\n", head->ID, head->name, head->quota,
               head->department_student_head, head->next);
        head = head->next;
    }
    printf("---That's all in the linked list---\n");
}

void search_node(char dataType, void *input_head, long long int ID)
{
    if (dataType == 's' || dataType == 'S') { // student
        Student *head = ((Student *)input_head);

        printf("Searching for student ID %lld\n", ID);

        int flag = 0;
        while (head) {
            if (head->ID == ID) {
                printf("ID %lld found.\n", ID);
                flag = 1;
                break;
            }
            head = head->next;
        }

        if (flag) {
            printf("The info of student ID %lld\n", ID);
            printf("ID: %15lld, name: %s.\n"
                   "Grade: Chinese %2d, math %2d, English %2d, social studies %2d, "
                   "science %2d.\n"
                   "Choice 1.%5lld 2.%5lld 3.%5lld 4.%5lld 5.%5lld 6.%5lld\n",
                   head->ID, head->name, head->grade.chinese, head->grade.english,
                   head->grade.math, head->grade.social_science, head->grade.science,
                   head->choice[0].department_ID, head->choice[1].department_ID,
                   head->choice[2].department_ID, head->choice[3].department_ID,
                   head->choice[4].department_ID, head->choice[5].department_ID);
        } else {
            printf("The student ID %lld not found\n", ID);
        }
    } else if (dataType == 'd' || dataType == 'D') { // department
        Department *head = (Department *)input_head;

        printf("Searching for department ID %lld\n", ID);

        int flag = 0;
        while (head) {
            if (head->ID == ID) {
                printf("ID %lld found.\n", ID);
                flag = 1;
                break;
            }
            head = head->next;
        }

        if (flag) {
            printf("The info of department ID %lld\n", ID);
            printf("ID: %lld, name: %s, quota: %d\n", head->ID, head->name,
                   head->quota);
        } else {
            printf("The department ID %lld not found\n", ID);
        }
    } else {
        printf("This shouldn't happen! %s %d\n", __FILE__, __LINE__);
        exit(0);
    }
}