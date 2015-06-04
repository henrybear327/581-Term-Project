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

    printf("Student ID starting with? ");
    long long int ID;
    scanf("%lld", &ID);

    printf("How many department is available? ");
    int department;
    scanf("%d", &department);
    printf("Department ID starting with? ");
    long long int department_ID;
    scanf("%lld", &department_ID);

    for (int i = 0; i < quantity; i++) {
        int book[department];
        long long int result[6] = { 0 };
        memset(book, 0, sizeof(book));
        for (int i = 0; i < department && i < 6; i++) {
            int temp = rand() % department;
            if (book[temp] == 0) {
                book[temp] = 1;
                result[i] = temp + department_ID;
            } else {
                i--;
            }
        }
        // student name default omit
        fprintf(pFile,
                "%15lld omit %2d %2d %2d %2d %2d %lld %lld %lld %lld %lld %lld\n",
                ID++, rand() % 16, rand() % 16, rand() % 16, rand() % 16,
                rand() % 16, result[0], result[1], result[2], result[3], result[4],
                result[5]);
    }

    fclose(pFile);

    return 0;
}