#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include "dataType.h"

/*
Enqueue all data in student.txt
*/
Student *enqueue_all_student_records(FILE *pStudentData);

/*
Show all data node in queue given the Student head pointer
*/
void show_queue(Student *head);

/*
Remove the first node of the queue
*/
Student *pop(Student *head);

/*
Push a Student node into the queue and update previously last node accordingly
*/
void push(Student *node, Student *tail);

void edit_student_data(Student *head, long long int ID);

// useless : front -> just check the head pointer
// Student *front(Student *head);

// useless : just check if head is NULL
// bool *is_empty(Student *head);

Student *insert_student_data(Student *current, long long int ID);

Student *delete_student_data(Student *current, long long int ID);

#endif