#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "getInput.h"
#include "linkedList.h"
#include "queue.h"
#include "dataType.h"
#include "utility.h"

// git log --stat --decorate --pretty=full --graph

/*
*   ranking system
*   data verification (replication, non-existence department, etc.)
*
*   limitation
*   1. name can only be one word(no space because using %s to scan)
*
*   Some thoughts
*   1. Write copious and elaborate details about how and what the function that
*   I wrote does. This is a time saver and a better way to keep the program
*bug-free.
*   2. Always consider extreme cases, such as empty file, NULL pointer
*possibilities
*   3. Be good at using pointer!!!
*/

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

    /*
    //try queue pop(), clear and free all node
    while (student_head) {
        printf("Pop a node out from queue\n");
        student_head = pop(student_head);
        show_queue(student_head);
    }
    */
#endif

    // read all data from department.txt
    Department *department_head = load_department_data(pDepartmentData);

#if DEBUG
    show_all_node(department_head);
#endif
    /*
    initial condition
        all of the student data is in queue
        all of the department data is in a linked list
    */

    // query system UI
    printf("Before processing data, what do you want to do?\n");
    printf("\n(I)nsert, (D)elete, (E)dit, (S)earch, (W)rite to file, (L)ist "
           "all(from file), \n"
           "or press any other key to continue...\n> ");
    char choice[100];
    while (1) {
        while (fgets(choice, 100, stdin) == NULL || choice[0] == '\n') {
            printf("\n(I)nsert, (D)elete, (E)dit, (S)earch, (W)rite to file, (L)ist "
                   "all(from file), \n"
                   "or press any other key to continue...\n> ");
        }
        if (choice[0] == 'I' || choice[0] == 'i') {
            clear_screen();
            printf("Insert! Insert (S)tudent or (D)epartment?\n> ");

            char c;
            long long int ID;
            scanf("%c", &c);

            if (c == 's' || c == 'S') {
                printf("ID to insert? ");
                scanf("%lld", &ID);
                getchar();
                student_head = insert_student_data(student_head, ID);
            } else if (c == 'd' || c == 'D') {
                printf("ID to insert? ");
                scanf("%lld", &ID);
                getchar();
                department_head = insert_department_data(department_head, ID);
            } else {
                printf("Invalid choice\n");
            }
        } else if (choice[0] == 'D' || choice[0] == 'd') {
            clear_screen();
            printf("Delete! Delete (S)tudent or (D)epartment? (C)ancel?\n> ");

            char c;
            long long int ID;
            scanf("%c", &c);
            if (c == 'c' || c == 'C') {
                printf("Operation cancelled\n");
                continue;
            }

            if (c == 's' || c == 'S') {
                printf("ID to delete? ");
                scanf("%lld", &ID);
                getchar();
                student_head = delete_student_data(student_head, ID);
            } else if (c == 'd' || c == 'D') {
                printf("ID to delete? ");
                scanf("%lld", &ID);
                getchar();
                department_head = delete_department_data(department_head, ID);
            } else {
                printf("Invalid choice\n");
            }

        } else if (choice[0] == 'E' || choice[0] == 'e') {
            clear_screen();
            printf("Edit! Edit (S)tudent or (D)epartment?\n> ");

            char c;
            long long int ID;
            scanf("%c", &c);

            if (c == 's' || c == 'S') {
                printf("ID to modify? ");
                scanf("%lld", &ID);
                getchar();
                edit_student_data(student_head, ID);
            } else if (c == 'd' || c == 'D') {
                printf("ID to modify? ");
                scanf("%lld", &ID);
                getchar();
                edit_department_data(department_head, ID);
            } else {
                printf("Invalid choice\n");
            }
        } else if (choice[0] == 'S' || choice[0] == 's') {
            clear_screen();
            printf("Search! Search (S)tudent or (D)epartment by ID?\n> ");
            char c;
            long long int ID;
            scanf("%c %lld", &c, &ID);
            getchar();
            if (c == 's' || c == 'S')
                search_node(c, student_head, ID);
            else if (c == 'd' || c == 'D')
                search_node(c, department_head, ID);
            else
                printf("Invalid choice\n");
        } else if (choice[0] == 'W' || choice[0] == 'w') {
            clear_screen();
            printf("Save file! Save (S)tudent or (D)epartment data to file?\n> ");
            char c;
            scanf("%c", &c);
            getchar();
            if (c == 's' || c == 'S') {
                // close FILE stream first, and then get new one from the function
                fclose(pStudentData);
                pStudentData = save_student_data(student_head);
            } else if (c == 'd' || c == 'D') {
                fclose(pDepartmentData);
                pDepartmentData = save_department_data(department_head);
            } else {
                printf("Invalid choice\n");
            }
        } else if (choice[0] == 'L' || choice[0] == 'l') {
            clear_screen();
            printf("List all data! List (S)tudent or (D)epartment data?\n> ");
            char c;
            scanf("%c", &c);
            getchar();
            printf("First from file then from memory!\n");
            if (c == 's' || c == 'S') {
                // reopen FLIE stream to get latest data
                fclose(pStudentData);
                pStudentData = get_student_txt_fp();
                show_student_txt(pStudentData);

                show_queue(student_head);
            } else if (c == 'd' || c == 'D') {
                fclose(pDepartmentData);
                pDepartmentData = get_department_txt_fp();
                show_department_txt(pDepartmentData);

                show_all_node(department_head);
            } else {
                printf("Invalid choice\n");
            }
        } else {
            printf("Are you sure to move on?[y/n]\n");
            char c;
            c = getchar();
            if (c == 'n' || c == 'N') {
                continue;
            }

            clear_screen();
            printf("Automatically saving changes for you...\n");
            fclose(pStudentData);
            pStudentData = save_student_data(student_head);
            fclose(pDepartmentData);
            pDepartmentData = save_department_data(department_head);

            printf("Let's move on......\n");
            break;
        }

        printf("\n(I)nsert, (D)elete, (E)dit, (S)earch, (W)rite to file, (L)ist "
               "all, \n"
               "or press any other key to continue...\n> ");
    }

    /*
    All update-to-date information of students and departments is in the memory
    and saved to respective text files.

    Now it's time to implement the ranking system!
    */

    if (student_head == NULL || department_head == NULL) {
        printf("There isn't sufficient to keep the system running!\n"
               "Terminating the program\n");
        exit(0);
    }

    // need to set terminating condition
    clear_screen();
    while (student_head) { // when the queue is empty, the work is done!
        // put all students from queue to the corresponding department
        while (student_head) {
            // copy the front student node, and then attach to the corresponding
            // department
            Student *new_node = calloc(1, sizeof(Student));
            if (new_node == NULL) {
                CALLOC_ERROR;
                exit(0);
            }
            memcpy(new_node, student_head, sizeof(Student));
#if DEBUG
            printf("department_head %p\n", department_head);
#endif
            add_student_to_department(department_head, new_node);
#if DEBUG
            printf("Pop ID %lld out from queue\n", student_head->ID);
#endif
            student_head = pop(student_head);
#if DEBUG
            printf("\n\n");
            show_queue(student_head);
            show_all_node(department_head);
            printf("\n\n");
#endif
        }
        printf("Done!\n");

        // eliminate the excessive students, and then put them in queue
        // check if the current_result runs over 5
    }
    // Student *student_tail = find_queue_tail(student_head);

    // program ending, clean up
    if (fclose(pStudentData) == EOF)
        printf("Error closing pStudentData\n");
    if (fclose(pDepartmentData) == EOF)
        printf("Error closing pDepartmentData\n");

    return 0;
}