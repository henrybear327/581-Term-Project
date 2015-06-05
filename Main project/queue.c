#include <stdio.h>
#include <stdlib.h>

#include "dataType.h"

/*
No bitch-proof! Invalid input file may crash the program
*/
Student *enqueue_all_student_records(FILE *pStudentData)
{
    int count = 0;

    Student *head = calloc(1, sizeof(Student));
    if (head == NULL) {
        CALLOC_ERROR;
        exit(0);
    }

    // http://www.cplusplus.com/reference/cstdio/fscanf/
    // http://www.cplusplus.com/reference/cstdio/rewind/

    //      403410000 omit  3  1  5 10  4
    rewind(pStudentData); // Sets the position indicator associated with stream to
    // the beginning of the file.

    Student *prev = NULL;
    while (1) {
        if (count == 0) {
            if (fscanf(pStudentData,
                       "%lld %s %d %d %d %d %d %lld %lld %lld %lld %lld %lld",
                       &head->ID, head->name, &head->grade.chinese,
                       &head->grade.english, &head->grade.math,
                       &head->grade.social_science, &head->grade.science,
                       &head->choice[0].department_ID, &head->choice[1].department_ID,
                       &head->choice[2].department_ID, &head->choice[3].department_ID,
                       &head->choice[4].department_ID,
                       &head->choice[5].department_ID) != EOF) {
                count++;
                head->next = NULL;
                prev = head;
            } else {
                printf("Read %d student data to queue\n", count);
                break;
            }
        } else {
            Student *new_node = calloc(1, sizeof(Student));
            if (new_node == NULL) {
                CALLOC_ERROR;
                exit(0);
            }

            if (fscanf(pStudentData,
                       "%lld %s %d %d %d %d %d %lld %lld %lld %lld %lld %lld",
                       &new_node->ID, new_node->name, &new_node->grade.chinese,
                       &new_node->grade.english, &new_node->grade.math,
                       &new_node->grade.social_science, &new_node->grade.science,
                       &new_node->choice[0].department_ID,
                       &new_node->choice[1].department_ID,
                       &new_node->choice[2].department_ID,
                       &new_node->choice[3].department_ID,
                       &new_node->choice[4].department_ID,
                       &new_node->choice[5].department_ID) != EOF) {
                count++;
                new_node->next = NULL;
                prev->next = new_node;
                prev = new_node;
            } else {
                printf("---Enqueued %d student data---\n", count);
                break;
            }
        }
    }

    return head;
}

void show_queue(Student *head)
{
    printf("---showing queue(front)---\n");
    while (head) {
        printf("%15lld %s %2d %2d %2d %2d %2d %5lld %5lld %5lld %5lld %5lld %5lld "
               "%d\n",
               head->ID, head->name, head->grade.chinese, head->grade.english,
               head->grade.math, head->grade.social_science, head->grade.science,
               head->choice[0].department_ID, head->choice[1].department_ID,
               head->choice[2].department_ID, head->choice[3].department_ID,
               head->choice[4].department_ID, head->choice[5].department_ID,
               head->current_result);
        head = head->next;
    }
    printf("---That's all in the queue(back)---\n");
}

Student *pop(Student *head)
{
    Student *next = head->next;
    free(head);

    return next;
}
