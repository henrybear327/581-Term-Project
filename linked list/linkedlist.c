#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linkedlist.h"

void test()
{
    printf("Hello World\n");
}

// create a new node and update the second-to-last node's next pointer

// can use Node *create_code..., too.
void create_node(Node **tail, int value)
{
    /*
    Take the first time for example
    addr	var_name	type		value
    0x001	head		ptr to Node	NULL
    0x010	tail		ptr to ptr 	0x001
    0x100	new_node	ptr to Node 0x200

    If I print out tail, I am viewing head's addr.
    If I print out *tail, I am viewing head's value.
    */
    Node *new_node = malloc(sizeof(Node));
    assert(new_node != NULL); // always check malloc fail or not

    if (*tail != NULL)          // check if this is the first node
        (*tail)->next = new_node; // update prev node's next

    new_node->prev = *tail;
    new_node->data = value;
    new_node->next = NULL;

    *tail = new_node;
    return;
}

// show all nodes from the oldest to newest
void show_nodes(Node *head)
{
    int count = 0;
    while (head != NULL) {
        printf("node %2d has value %2d. Cur %p Prev %p Next %p\n", count++,
               head->data, head, head->prev, head->next);
        head = head->next;
    }
    return;
}

int list_length(Node *head)
{
    if (head == NULL)
        return 0;

    int length = 1;
    while (head->next != NULL) {
        length++;
        head = head->next;
    }
    return length;
}