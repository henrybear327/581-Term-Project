void test();

typedef struct node Node;

struct node {
    Node *prev;

    int data;

    Node *next;
};

// Get the length of the linked list
int list_length(Node *head);

// create new node and update the second-to-last node pointer
void create_node(Node **, int);

// show all nodes
void show_nodes(Node *);

// insert the node after specified data

// delete the node with particular data

// delete the node with the specified index

// search for the particular data