#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataType.h"
#include "queue.h"

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
                head->grade.total = head->grade.chinese + head->grade.english +
                                    head->grade.math + head->grade.social_science +
                                    head->grade.science;
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
                new_node->grade.total = new_node->grade.chinese +
                                        new_node->grade.english + new_node->grade.math +
                                        new_node->grade.social_science +
                                        new_node->grade.science;
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

    return count == 0 ? NULL : head;
}

void show_queue(Student *head)
{
    printf("---showing queue(front)---\n");
    while (head) {
        printf("%15lld %8s %2d %2d %2d %2d %2d %2d %5lld %5lld %5lld %5lld %5lld "
               "%5lld "
               "%d\n",
               head->ID, head->name, head->grade.chinese, head->grade.english,
               head->grade.math, head->grade.social_science, head->grade.science,
               head->grade.total, head->choice[0].department_ID,
               head->choice[1].department_ID, head->choice[2].department_ID,
               head->choice[3].department_ID, head->choice[4].department_ID,
               head->choice[5].department_ID, head->current_result);
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
            head->grade.total = head->grade.chinese + head->grade.english +
                                head->grade.math + head->grade.social_science +
                                head->grade.science;
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
#if DEBUG
    printf("current = %p\n", current);
#endif
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
#if DEBUG
                printf("Insert before head\n");
#endif
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
                new_node->grade.total = new_node->grade.chinese +
                                        new_node->grade.english + new_node->grade.math +
                                        new_node->grade.social_science +
                                        new_node->grade.science;
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
#if DEBUG
                printf("Insert before current node %lld\n", current->ID);
#endif
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
                new_node->grade.total = new_node->grade.chinese +
                                        new_node->grade.english + new_node->grade.math +
                                        new_node->grade.social_science +
                                        new_node->grade.science;
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

    Student *new_node = calloc(1, sizeof(Student));
    if (new_node == NULL) {
        CALLOC_ERROR;
        exit(0);
    }

#if DEBUG
    printf("Insert after tail\n");
#endif
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
    new_node->grade.total =
        new_node->grade.chinese + new_node->grade.english + new_node->grade.math +
        new_node->grade.social_science + new_node->grade.science;
    printf("Priority of choice? ");
    scanf("%lld %lld %lld %lld %lld %lld", &new_node->choice[0].department_ID,
          &new_node->choice[1].department_ID, &new_node->choice[2].department_ID,
          &new_node->choice[3].department_ID, &new_node->choice[4].department_ID,
          &new_node->choice[5].department_ID);
    getchar(); // dangling \n

    if (prev != NULL)
        prev->next = new_node;
    else
        head = new_node;

    return head;
}

Student *delete_student_data(Student *current, long long int ID)
{
    Student *head = current, *prev = NULL;
    while (current) {
        if (ID == current->ID) {
            if (prev == NULL) {
                head = current->next;
                free(current);

                printf("ID %lld deleted\n", ID);
                return head;
            } else {
                if (current->next == NULL) {
                    prev->next = NULL;
                    free(current);

                    printf("ID %lld deleted\n", ID);
                    return head;
                } else {
                    prev->next = current->next;
                    free(current);

                    printf("ID %lld deleted\n", ID);
                    return head;
                }
            }
        }

        prev = current;
        current = current->next;
    }

    printf("Student ID %lld not found\n", ID);
    return head;
}

Student *find_queue_tail(Student *head)
{
    Student *prev = NULL;
    while (head) {
        prev = head;
        head = head->next;
    }

    return prev;
}

void add_student_to_department(Department *department_head,
                               Student *student_node, Student **queue_head)
{
#if DEBUG
    printf("department_head %p\n", department_head);
#endif
    Department *original_department_head = department_head;

    // possible NULL?
    while (department_head) { // loop through department nodes to find ID
        if (department_head->ID ==
            student_node->choice[student_node->current_result]
            .department_ID) { // ID matched
#if DEBUG
            printf("Department ID %lld matched(%lld)\n", department_head->ID,
                   student_node->choice[student_node->current_result].department_ID);
#endif
            (department_head->total_student)++;

            // insert the student node under this department

            Student *original_department_student_head =
                department_head->department_student_head;

            Student **current = &department_head->department_student_head;
#define current (*current)
            if (current == NULL) {
// no student yet
#if DEBUG
                printf(
                    "Add first student node %lld to department\n",
                    student_node->choice[student_node->current_result].department_ID);
                printf("student_node %p\n", student_node);
#endif

                current = student_node;

#if DEBUG
                printf("current %p\n", current);
#endif

                student_node->next = NULL;

#if DEBUG
                printf("department_head->department_student_head %p\n",
                       department_head->department_student_head);
#endif

                department_head = original_department_head;
                return;
            }

            Student *prev = NULL;
            while (current) {
                if (student_node->grade.total > current->grade.total) {
                    if (prev == NULL) { // before first node
#if DEBUG
                        printf("Add student node %lld before head to department\n",
                               student_node->choice[student_node->current_result]
                               .department_ID);
#endif

                        student_node->next = current;
                        current = student_node;

                        department_head = original_department_head;
                        return;
                    } else {
// after first node and before last node
#if DEBUG
                        printf("Add student node %lld b/w head and tail to department\n",
                               student_node->choice[student_node->current_result]
                               .department_ID);
#endif

                        prev->next = student_node;
                        student_node->next = current;

                        department_head->department_student_head =
                            original_department_student_head;
                        department_head = original_department_head;
                        return;
                    }
                }

                prev = current;
                current = current->next;
            }
// after last node
#if DEBUG
            printf("Add student node %lld in the end to department\n",
                   student_node->choice[student_node->current_result].department_ID);
#endif

            prev->next = student_node;
            student_node->next = NULL;

            department_head->department_student_head =
                original_department_student_head;
            department_head = original_department_head;
            return;
        }

        department_head = department_head->next;
    }

    printf("Student ID %lld error! Requested department ID %lld not found!\n",
           student_node->ID,
           student_node->choice[student_node->current_result].department_ID);

    if ((student_node->current_result) + 1 == 6) {
        department_head = original_department_head;
        return;
    }
    // directly enqueue student
    push_to_queue(queue_head, student_node);
    department_head = original_department_head;
    return;
}

void push_to_queue(Student **queue_head, Student *to_enqueue)
{
    Student *prev = NULL, *current_queue_pos = *queue_head;
    while (current_queue_pos) {
        prev = current_queue_pos;
        current_queue_pos = current_queue_pos->next;
    }

    while (to_enqueue && to_enqueue->current_result >= 6) {
#if DEBUG
        printf("1\n");
#endif
        // don't need to enqueue this kind of student
        printf("No department! %15lld %8s %2d %2d %2d %2d %2d %2d %5lld %5lld "
               "%5lld %5lld "
               "%5lld %5lld %d\n",
               to_enqueue->ID, to_enqueue->name, to_enqueue->grade.chinese,
               to_enqueue->grade.english, to_enqueue->grade.math,
               to_enqueue->grade.social_science, to_enqueue->grade.science,
               to_enqueue->grade.total, to_enqueue->choice[0].department_ID,
               to_enqueue->choice[1].department_ID,
               to_enqueue->choice[2].department_ID,
               to_enqueue->choice[3].department_ID,
               to_enqueue->choice[4].department_ID,
               to_enqueue->choice[5].department_ID, to_enqueue->current_result);
        to_enqueue = to_enqueue->next;
    }

    // don't forget the NULL case
    // if prev is NULL, prev-next will simply crash the program
    if (prev) {
        prev->next = to_enqueue;
    } else {
        *queue_head = to_enqueue;
    }

    while (to_enqueue) {
        (to_enqueue->current_result)++;
        if (to_enqueue->current_result == 6) {
#if DEBUG
            printf("2\n");
#endif
            printf("No department! %15lld %8s %2d %2d %2d %2d %2d %2d %5lld %5lld "
                   "%5lld %5lld "
                   "%5lld %5lld %d\n",
                   to_enqueue->ID, to_enqueue->name, to_enqueue->grade.chinese,
                   to_enqueue->grade.english, to_enqueue->grade.math,
                   to_enqueue->grade.social_science, to_enqueue->grade.science,
                   to_enqueue->grade.total, to_enqueue->choice[0].department_ID,
                   to_enqueue->choice[1].department_ID,
                   to_enqueue->choice[2].department_ID,
                   to_enqueue->choice[3].department_ID,
                   to_enqueue->choice[4].department_ID,
                   to_enqueue->choice[5].department_ID, to_enqueue->current_result);

            if (prev == NULL) {
                // printf("prev==NULL\n");
                to_enqueue = to_enqueue->next;
                continue;
            }

            prev->next = to_enqueue->next;
            to_enqueue = to_enqueue->next;
            continue;
        }
        prev = to_enqueue;
        to_enqueue = to_enqueue->next;
    }
}