#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getInput.h"
#include "linkedList.h"
#include "queue.h"

#define QUALIFIED 1
#define WAITING_LIST 2
#define REJECT 3

#define NAME_SIZE 100

typedef struct result Result;
typedef struct grade Grade;
typedef struct student Student;
typedef struct department Department;

struct result { //放榜結果 系所,正/備/未錄取
    long long int department_ID;
    int result_state;
};

struct grade { //學測成績
    int chinese;
    int english;
    int math;
    int social_science;
    int science;

    int total;
};

struct department { //系所資料
    // to-do 錄取計算方式
    long long int ID;
    char name[NAME_SIZE];

    int quota;
    Student *head;
};

struct student {
    long long int student;
    char name[NAME_SIZE];

    Grade grade;
    Department choice[6]; // 志願序
    int current_result;   //目前跑到第幾志願

    Student *next;
};

int main()
{
    /*
    Rule of thumb

    read information from the text file

    所有學生錄取第一志願
    超額比序，多的進入queue
    */

    FILE *pStudentData = get_student_txt_fp();
    show_student_txt(pStudentData);
    FILE *pDepartmentData = get_department_txt_fp();
    show_department_txt(pDepartmentData);

    return 0;
}