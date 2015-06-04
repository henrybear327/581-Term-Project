#include <stdio.h>
#include <stdlib.h>

FILE *get_student_txt_fp()
{
    FILE *pFile;
    pFile = fopen("student.txt",
                  "r"); // http://www.cplusplus.com/reference/cstdio/fopen/

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