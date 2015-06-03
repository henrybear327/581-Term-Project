#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include "dataType.h"

Student *enqueue_all_student_records(*FILE);

/*
Push a Student node into the queue and update previously last node accordingly
*/
void push(Student *node, Student *tail);

void pop(Student *head);

Student *front(Student *head);

Student *back(Student *tail);

#endif