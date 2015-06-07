#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dataType.h"
#include "queue.h"
#include "utility.h"

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
        printf("%5lld %8s %3d %3d %p %p\n", head->ID, head->name, head->quota,
               head->total_student, head->department_student_head, head->next);

        Student *temp = head->department_student_head;
        if (temp)
            printf("Student data of department %lld\n", head->ID);

        while (temp != NULL) {
            printf("%15lld %8s %2d %2d %2d %2d %2d %2d %5lld %5lld %5lld %5lld %5lld "
                   "%5lld "
                   "%d\n",
                   temp->ID, temp->name, temp->grade.chinese, temp->grade.english,
                   temp->grade.math, temp->grade.social_science, temp->grade.science,
                   temp->grade.total, temp->choice[0].department_ID,
                   temp->choice[1].department_ID, temp->choice[2].department_ID,
                   temp->choice[3].department_ID, temp->choice[4].department_ID,
                   temp->choice[5].department_ID, temp->current_result);
            temp = temp->next;
            // printf("temp %p\n", temp);
        }

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

#if DEBUG
                printf("Insert before head\n");
#endif
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

#if DEBUG
                printf("Insert before current node %lld\n", ID);
#endif
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
        } else if (ID == current->ID) {
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

#if DEBUG
    printf("Insert after tail\n");
#endif
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

void eliminate_student_from_department(Department *current_department,
                                       Student **queue_head)
{
    while (current_department) {
#if DEBUG
        printf("department %lld in eliminate_student_from_department\n",
               current_department->ID);
#endif
        if (current_department->quota < current_department->total_student) {
            // need to eliminate
            /*
            two situations
            1. only one qualify for the last slot
            2. more than one qualify for the last slot
            */

            Student *prev = NULL,
                     *current_student = current_department->department_student_head;
            int count = 0, worst_total_grade = current_student->grade.total;

            if (current_department->quota == 0 &&
                current_department->total_student != 0) { // no quota at all
#if DEBUG
                printf("No quota for department %lld\n", current_department->ID);
#endif
                current_department->total_student = 0;
                push_to_queue(queue_head, current_student);
                current_department->department_student_head = NULL;
                current_department = current_department->next;
                continue;
            }

            while (current_student) {
                count++;
                if (count > current_department->quota) {
                    if (worst_total_grade > current_student->grade.total) {
                        // update department total_student,show last qualified student grade
                        // data
                        current_department->total_student = count - 1;
#if DEBUG
                        printf("Last qualified student grade data of department %lld\n",
                               current_department->ID);
                        printf("%15lld %8s %2d %2d %2d %2d %2d %2d %5lld %5lld %5lld %5lld "
                               "%5lld "
                               "%5lld "
                               "%d\n",
                               prev->ID, prev->name, prev->grade.chinese,
                               prev->grade.english, prev->grade.math,
                               prev->grade.social_science, prev->grade.science,
                               prev->grade.total, prev->choice[0].department_ID,
                               prev->choice[1].department_ID, prev->choice[2].department_ID,
                               prev->choice[3].department_ID, prev->choice[4].department_ID,
                               prev->choice[5].department_ID, prev->current_result);
#endif
                        // enqueue the following nodes
                        prev->next = NULL;
                        push_to_queue(queue_head, current_student);
                        break;
                    }
                }

                prev = current_student;
                current_student = current_student->next;
            }
        }

        current_department = current_department->next;
    }
}

void show_final_result(Department *head)
{

    clear_screen();

    printf("---Showing all department's result---\n");
    while (head) {
        /*
        printf("%5lld %8s %3d %3d %p %p\n", head->ID, head->name, head->quota,
               head->total_student, head->department_student_head, head->next);
        */

        Student *temp = head->department_student_head;
        if (temp)
            printf("Student data of department %lld\n", head->ID);

        while (temp != NULL) {
            printf("%15lld %8s %2d %2d %2d %2d %2d %2d %5lld %5lld %5lld %5lld %5lld "
                   "%5lld "
                   "%d\n",
                   temp->ID, temp->name, temp->grade.chinese, temp->grade.english,
                   temp->grade.math, temp->grade.social_science, temp->grade.science,
                   temp->grade.total, temp->choice[0].department_ID,
                   temp->choice[1].department_ID, temp->choice[2].department_ID,
                   temp->choice[3].department_ID, temp->choice[4].department_ID,
                   temp->choice[5].department_ID, temp->current_result);
            temp = temp->next;
            // printf("temp %p\n", temp);
        }

        head = head->next;
    }
    printf("---That's all in the linked list---\n");
}