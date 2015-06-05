#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*clang-format-3.5 -i -style=LLVM  generate_department.c && astyle --style=linux
 * generate_department.c && clang -Wall -Wextra generate_department.c -o
 * generate_department.o*/

int main()
{
    /*
    struct student {
        long long int student;
        char name[NAME_SIZE];

        Grade grade;
        Department choice[6]; // 志願序
        int current_result;   //目前跑到第幾志願

        Student *next;
    };
    */
    srand(time(NULL));

    FILE *pFile;
    pFile = fopen("department.txt", "w");

    if (pFile == NULL) {
        printf("Error opening file. Terminating...\n");
        return 0;
    }

    printf("How many department is available? ");
    int department;
    scanf("%d", &department);
    printf("Department ID starting with-> 0\n");
    long long int department_ID = 0;
    // scanf("%lld", &department_ID);
    printf("Maximum quota per department? ");
    int quota;
    scanf("%d", &quota);

    for (int i = 0; i < department; i++) {
        fprintf(pFile, "%5lld omit %2d\n", department_ID++, rand() % (quota)+1);
    }

    fclose(pFile);

    return 0;
}