/*
    ###################
    ### LINKED LIST ###
    ###################
    ###   By Marci  ###
    ###################
*/

#include <stdio.h>
#include <stdlib.h>

enum insert_direction {FIRST, LAST};

typedef struct node {
    int data;
    struct node *next;
} node_t;

// Basic functions
node_t* create_node (int data);
void insert_node(int data, enum insert_direction where);
node_t* search_node(int data);
void remove_node(int data);

// Print functions
void print_node(node_t* temp);
void print_linked_list();

node_t* head = NULL;

int main()
{
    insert_node(10, LAST);
    insert_node(20, FIRST);
    insert_node(30, LAST);
    insert_node(66, FIRST);

    print_linked_list();

    print_node(search_node(20));

    remove_node(20);

    print_node(search_node(20));

    print_linked_list();

    return 0;
}

node_t* create_node (int data)
{
    node_t * temp_node = (node_t*)malloc(sizeof(node_t));
    temp_node -> data = data;
    temp_node -> next = NULL;
    return temp_node;
}

void insert_node(int data, enum insert_direction where)
{
    node_t *temp_node = create_node(data);

    if (head == NULL) {
        head = temp_node;
        return;
    }

    if (where == FIRST) {
        temp_node -> next = head;
        head = temp_node;
        return;
    }

    if (where == LAST) {

        node_t *ptr = head;

        while (ptr -> next != NULL) {
            ptr = ptr -> next;
        }

        ptr -> next = temp_node;
    }
}

void print_linked_list()
{
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    node_t *ptr = head;

    while (ptr -> next != NULL) {
        printf("%d -> ", ptr -> data);
        ptr = ptr -> next;
    }

    printf("%d\n", ptr -> data);
}

void print_node(node_t* temp)
{
    if (temp == NULL) {
        printf("Node is NULL\n");
        return;
    }

    if (temp -> next != NULL)
        printf("%d -> %d\n", temp -> data, (temp -> next) ->data);
    else
        printf("%d\n", temp -> data);
}

node_t* search_node(int data)
{
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    node_t *ptr = head;

    // While loop goes until finds the target node or end of the list.
    while (ptr != NULL) {
        if (ptr -> data == data)
            break;
        ptr = ptr -> next;
    }

    return ptr;
}

void remove_node(int data)
{
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    node_t *current_node = head;
    node_t *prev_node = NULL;

    // This loop will stop if finds the target node, or the list ends.
    while (current_node != NULL) {

        if (current_node -> data == data)
            break;

        prev_node = current_node;
        current_node = current_node -> next;
    }

    // If data isn't in the list
    if (current_node == NULL) {
        printf("cant delete %d it isn't in the list.\n", data);
        return;
    }

    // Target node was the first one
    if (prev_node == NULL) {

        // If there are at least 2 elements.
        if (current_node -> next != NULL) {
            head = current_node -> next;
        }

        // If the list has only one element.
        free(current_node);

        return;
    }

    // Target node was the last one
    if (current_node -> next == NULL) {
        prev_node -> next = NULL;
        free(current_node);
        return;
    }

    // If node was between two nodes
    prev_node -> next = current_node -> next;
    free(current_node);
}






