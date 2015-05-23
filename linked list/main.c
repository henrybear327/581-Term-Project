#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

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
    }

    return 0;
}