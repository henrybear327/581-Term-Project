#ifndef DATATYPE_H
#define DATATYPE_H

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
    long long int ID;
    char name[NAME_SIZE];

    Grade grade;
    Department choice[6]; // 志願序
    int current_result;   //目前跑到第幾志願

    Student *next;
};

#define CALLOC_ERROR                                                           \
  printf("calloc() fails on line %d in file %s\n", __LINE__, __FILE__)

#endif