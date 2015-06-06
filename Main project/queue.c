#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
        printf("%15lld %8s %2d %2d %2d %2d %2d %5lld %5lld %5lld %5lld %5lld %5lld "
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

void edit_student_data(Student *head, long long int ID)
{
    // check for existence
    while (head) {
        if (head->ID == ID) {
            // change this record
            printf("Changing data of student ID = %lld\n", ID);
            printf("New name? (Current: %s) ", head->name);
            fgets(head->name, NAME_SIZE, stdin);
            // get rid of \n
            head->name[strlen(head->name) - 1] = '\0';
            printf("New grade? Enter using the order of Chinese, English, Math, "
                   "Social Science, Science\n(Current: %2d %2d %2d %2d %2d) ",
                   head->grade.chinese, head->grade.english, head->grade.math,
                   head->grade.social_science, head->grade.science);
            scanf("%d %d %d %d %d", &head->grade.chinese, &head->grade.english,
                  &head->grade.math, &head->grade.social_science,
                  &head->grade.science);
            printf("New priority of choice?\n (Current: %5lld %5lld %5lld %5lld "
                   "%5lld %5lld)",
                   head->choice[0].department_ID, head->choice[1].department_ID,
                   head->choice[2].department_ID, head->choice[3].department_ID,
                   head->choice[4].department_ID, head->choice[5].department_ID);
            scanf("%lld %lld %lld %lld %lld %lld)", &head->choice[0].department_ID,
                  &head->choice[1].department_ID, &head->choice[2].department_ID,
                  &head->choice[3].department_ID, &head->choice[4].department_ID,
                  &head->choice[5].department_ID);
            getchar(); // dangling \n

            return;
        }
        head = head->next;
    }

    printf("Student ID %lld doesn't exit!\n", ID);
}

Student *insert_student_data(Student *current, long long int ID)
{
    Student *head = current, *prev = NULL;
    while (current) {
        // printf("current ID %lld\n", current->ID);
        if (ID < current->ID) { // insert before it
            if (prev == NULL) {
                Student *new_node = calloc(1, sizeof(Student));
                if (new_node == NULL) {
                    CALLOC_ERROR;
                    exit(0);
                }

                printf("Insert before head\n");
                new_node->ID = ID;
                printf("New name? ");
                fgets(new_node->name, NAME_SIZE, stdin);
                // get rid of \n
                new_node->name[strlen(new_node->name) - 1] = '\0';
                printf("Grade? Enter using the order of Chinese, English, Math, "
                       "Social Science, Science: ");
                scanf("%d %d %d %d %d", &new_node->grade.chinese,
                      &new_node->grade.english, &new_node->grade.math,
                      &new_node->grade.social_science, &new_node->grade.science);
                printf("Priority of choice? ");
                scanf("%lld %lld %lld %lld %lld %lld",
                      &new_node->choice[0].department_ID,
                      &new_node->choice[1].department_ID,
                      &new_node->choice[2].department_ID,
                      &new_node->choice[3].department_ID,
                      &new_node->choice[4].department_ID,
                      &new_node->choice[5].department_ID);
                getchar(); // dangling \n

                new_node->next = current;
                return new_node;
            } else {
                Student *new_node = calloc(1, sizeof(Student));
                if (new_node == NULL) {
                    CALLOC_ERROR;
                    exit(0);
                }

                printf("Insert before current node %lld\n", ID);
                new_node->ID = ID;
                printf("New name? ");
                fgets(new_node->name, NAME_SIZE, stdin);
                // get rid of \n
                new_node->name[strlen(new_node->name) - 1] = '\0';
                printf("Grade? Enter using the order of Chinese, English, Math, "
                       "Social Science, Science: ");
                scanf("%d %d %d %d %d", &new_node->grade.chinese,
                      &new_node->grade.english, &new_node->grade.math,
                      &new_node->grade.social_science, &new_node->grade.science);
                printf("Priority of choice? ");
                scanf("%lld %lld %lld %lld %lld %lld",
                      &new_node->choice[0].department_ID,
                      &new_node->choice[1].department_ID,
                      &new_node->choice[2].department_ID,
                      &new_node->choice[3].department_ID,
                      &new_node->choice[4].department_ID,
                      &new_node->choice[5].department_ID);
                getchar(); // dangling \n

                prev->next = new_node;
                new_node->next = current;

                return head;
            }
        } else if (ID == current->ID) {
            printf("Student ID %lld already exists.\n", ID);
            return head;
        }

        prev = current;
        current = current->next;
    }
    assert(ID >= prev->ID);

    Student *new_node = calloc(1, sizeof(Student));
    if (new_node == NULL) {
        CALLOC_ERROR;
        exit(0);
    }

    printf("Insert after tail\n");
    new_node->ID = ID;
    printf("New name? ");
    fgets(new_node->name, NAME_SIZE, stdin);
    // get rid of \n
    new_node->name[strlen(new_node->name) - 1] = '\0';
    printf("Grade? Enter using the order of Chinese, English, Math, "
           "Social Science, Science: ");
    scanf("%d %d %d %d %d", &new_node->grade.chinese, &new_node->grade.english,
          &new_node->grade.math, &new_node->grade.social_science,
          &new_node->grade.science);
    printf("Priority of choice? ");
    scanf("%lld %lld %lld %lld %lld %lld", &new_node->choice[0].department_ID,
          &new_node->choice[1].department_ID, &new_node->choice[2].department_ID,
          &new_node->choice[3].department_ID, &new_node->choice[4].department_ID,
          &new_node->choice[5].department_ID);
    getchar(); // dangling \n
    prev->next = new_node;

    return head;
}
