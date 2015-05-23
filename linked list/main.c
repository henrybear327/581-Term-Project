#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

#define DEBUG 1 // test this later

int main()
{
    test();

    Node *head = NULL, *tail = NULL;

    int input;

    while (scanf("%d", &input) != EOF) {
        if (head == NULL) {
            // send in head location to be updated
            create_node(&head, input);
            tail = head;
        } else {
            // send in tail location to be updated
            create_node(&tail, input);
        }
        show_nodes(head);
        printf("length is %d\n", list_length(head));
    }

    return 0;
}