#include <stdio.h>
#include <stdlib.h>

#include "dataType.h"

FILE *get_student_txt_fp()
{
    FILE *pFile;
    pFile = fopen("student.txt", "r");
    // http://www.cplusplus.com/reference/cstdio/fopen/

    if (pFile == NULL) {
        printf("Error opening student.txt. Terminating...\n");
        exit(0);
    }

    return pFile;
}

FILE *get_department_txt_fp()
{
    FILE *pFile;
    pFile = fopen("department.txt", "r");

    if (pFile == NULL) {
        printf("Error opening department.txt. Terminating...\n");
        exit(0);
    }

    return pFile;
}

void show_student_txt(FILE *pFile)
{
    rewind(pFile);
    // http://www.cplusplus.com/reference/cstdio/fgetc/
    printf("---show_student_txt---\n");
    char c = '\0';
    do {
        printf("%c", c);
        c = fgetc(pFile);
    } while (c != EOF);
    rewind(pFile);
    printf("---That's all in student.txt----\n");
}

void show_department_txt(FILE *pFile)
{
    rewind(pFile);
    // http://www.cplusplus.com/reference/cstdio/fgetc/
    printf("---show_department_txt---\n");
    char c = '\0';
    do {
        printf("%c", c);
        c = fgetc(pFile);
    } while (c != EOF);
    rewind(pFile);
    printf("---That's all in department.txt---\n");
}

FILE *save_student_data(Student *head)
{
    FILE *pFile;
    // clear student.txt
    pFile = fopen("student.txt", "w");
    // http://www.cplusplus.com/reference/cstdio/fopen/

    if (pFile == NULL) {
        printf("Error opening student.txt. Terminating...\n");
        exit(0);
    }

    while (head) {
        fprintf(pFile,
                "%15lld %s %2d %2d %2d %2d %2d %lld %lld %lld %lld %lld %lld\n",
                head->ID, head->name, head->grade.chinese, head->grade.english,
                head->grade.math, head->grade.social_science, head->grade.science,
                head->choice[0].department_ID, head->choice[1].department_ID,
                head->choice[2].department_ID, head->choice[3].department_ID,
                head->choice[4].department_ID, head->choice[5].department_ID);
        head = head->next;
    }

    fclose(pFile);

    // write data
    pFile = fopen("student.txt", "r");
    // http://www.cplusplus.com/reference/cstdio/fopen/

    if (pFile == NULL) {
        printf("Error opening student.txt. Terminating...\n");
        exit(0);
    }

    printf("Student data saved!\n");
    rewind(pFile);
    return pFile;
}

FILE *save_department_data(Department *head)
{
    FILE *pFile;
    // clear department.txt
    pFile = fopen("department.txt", "w");
    // http://www.cplusplus.com/reference/cstdio/fopen/

    if (pFile == NULL) {
        printf("Error opening department.txt. Terminating...\n");
        exit(0);
    }

    while (head) {
        fprintf(pFile, "%5lld %s %2d\n", head->ID, head->name, head->quota);
        head = head->next;
    }

    fclose(pFile);

    // write data
    pFile = fopen("department.txt", "r+");
    // http://www.cplusplus.com/reference/cstdio/fopen/

    if (pFile == NULL) {
        printf("Error opening department.txt. Terminating...\n");
        exit(0);
    }

    printf("Department data saved!\n");
    rewind(pFile);
    return pFile;
}