#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*clang-format-3.5 -i -style=LLVM  generate_student.c && astyle --style=linux
 * generate_student.c && clang -Wall -Wextra generate_student.c
 * -ogenerate_student.o*/

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
    pFile = fopen("student.txt", "w");

    if (pFile == NULL) {
        printf("Error opening file. Terminating...\n");
        return 0;
    }

    printf("How many student? ");
    int quantity;
    scanf("%d", &quantity);

    printf("ID starting with? ");
    long long int ID;
    scanf("%lld", &ID);

    for (int i = 0; i < quantity; i++) {
        // student name default omit
        fprintf(pFile, "%15lld omit %2d %2d %2d %2d %2d\n", ID++, rand() % 16,
                rand() % 16, rand() % 16, rand() % 16, rand() % 16);
    }

    fclose(pFile);

    return 0;
}