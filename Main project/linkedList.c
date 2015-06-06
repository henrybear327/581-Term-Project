#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dataType.h"

Department *load_department_data(FILE *pFile)
{
    rewind(pFile);
    bool no_data = false;

    Department *head = NULL;
    Department *prev = NULL;
    while (1) {
        if (head == NULL) {
            if ((head = calloc(1, sizeof(Department))) == NULL) {
                CALLOC_ERROR;
                exit(0);
            }
            if (fscanf(pFile, "%lld %s %d", &head->ID, head->name, &head->quota) ==
                EOF) {
                no_data = true;
                break;
            }

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
    return no_data ? NULL : head;
}

void show_all_node(Department *head)
{
    printf("---Showing all node---\n");
    while (head) {
        printf("%lld %8s %d %p %p\n", head->ID, head->name, head->quota,
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

void edit_department_data(Department *head, long long int ID)
{
    while (head) {
        if (head->ID == ID) {
            printf("Changing data of department ID = %lld\n", ID);
            printf("Name? (Current: %s) ", head->name);
            fgets(head->name, NAME_SIZE, stdin);
            head->name[strlen(head->name) - 1] = '\0';
            printf("Quota? (Current: %d) ", head->quota);
            scanf("%d", &head->quota);
            getchar();

            return;
        }
        head = head->next;
    }

    printf("Department ID %lld doesn't exist\n", ID);
}

Department *insert_department_data(Department *current, long long int ID)
{
    Department *head = current, *prev = NULL;
    while (current) {
        if (ID < current->ID) {
            if (prev == NULL) {
                Department *new_node;
                if ((new_node = calloc(1, sizeof(Department))) == NULL) {
                    CALLOC_ERROR;
                    exit(0);
                }

                printf("Insert before head\n");
                new_node->ID = ID;
                printf("Name? ");
                fgets(new_node->name, NAME_SIZE, stdin);
                new_node->name[strlen(new_node->name) - 1] = '\0';
                printf("Quota? ");
                scanf("%d", &new_node->quota);

                new_node->next = current;
                return new_node;
            } else {
                Department *new_node;
                if ((new_node = calloc(1, sizeof(Department))) == NULL) {
                    CALLOC_ERROR;
                    exit(0);
                }

                printf("Insert before current node %lld\n", ID);
                new_node->ID = ID;
                printf("Name? ");
                fgets(new_node->name, NAME_SIZE, stdin);
                new_node->name[strlen(new_node->name) - 1] = '\0';
                printf("Quota? ");
                scanf("%d", &new_node->quota);

                prev->next = new_node;
                new_node->next = current;

                return head;
            }
        } else if(ID == current->ID) {
            printf("ID %lld already exists\n", ID);
            return head;
        }

        prev = current;
        current = current->next;
    }

    Department *new_node;
    if ((new_node = calloc(1, sizeof(Department))) == NULL) {
        CALLOC_ERROR;
        exit(0);
    }

    printf("Insert after tail\n");
    new_node->ID = ID;
    printf("Name? ");
    fgets(new_node->name, NAME_SIZE, stdin);
    new_node->name[strlen(new_node->name) - 1] = '\0';
    printf("Quota? ");
    scanf("%d", &new_node->quota);

    if (prev != NULL)
        prev->next = new_node;
    else
        head = new_node;

    return head;
}

#define PRINT_DELETE_ID_MESSAGE printf("ID %lld deleted\n", ID);
Department *delete_department_data(Department *current, long long int ID)
{
    Department *head = current, *prev = NULL;
    while (current) {
        if (ID == current->ID) {
            if (prev == NULL) {
                head = current->next;
                free(current);

                PRINT_DELETE_ID_MESSAGE;
                return head;
            } else {
                if (current->next == NULL) {
                    prev->next = NULL;
                    free(current);

                    PRINT_DELETE_ID_MESSAGE;
                    return head;
                } else {
                    prev->next = current->next;
                    free(current);

                    PRINT_DELETE_ID_MESSAGE;
                    return head;
                }
            }
        }

        prev = current;
        current = current->next;
    }

    printf("Department ID %lld not found\n", ID);
    return head;
}