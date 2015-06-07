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

void edit_student_data(Student *head, long long int ID);

// useless : front -> just check the head pointer
// Student *front(Student *head);

// useless : just check if head is NULL
// bool *is_empty(Student *head);

Student *insert_student_data(Student *current, long long int ID);

Student *delete_student_data(Student *current, long long int ID);

/*
Push a Student node into the queue and update previously last node accordingly
*/

/*
Return the tail's memory address
*/
Student *find_queue_tail(Student *head);

/*
Given the original memory address of department_head and the original address of
student-node,
attach the student node to the respective department.
*/
void add_student_to_department(Department *department_head,
                               Student *student_node, Student **queue_head);

void push_to_queue(Student **queue_head, Student *to_enqueue);

#endif