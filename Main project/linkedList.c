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