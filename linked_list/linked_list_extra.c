/*
    #########################
    ### EXTRA LINKED LIST ###
    #########################
    ###      By Marci     ###
    #########################

    All element in the linked list has a previous and a next pointer.
    Adding element to the last place and searching are faster.
*/

#include <stdio.h>
#include <stdlib.h>

enum insert_direction {FIRST, LAST};

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node_t;

// Basic functions
node_t* create_node (int data);
void insert_node(int data, enum insert_direction where);
node_t* search_node(int data);
void remove_node(int data);

// Print functions
void print_node(node_t* temp);
void print_linked_list();

// Extra functions
// These are only for fun, I mean only works when the node stores data is an integer.
node_t* search_min();
node_t* search_max();
int summ_of_list();

// Global variables
node_t* head = NULL;
node_t* tail = NULL;
int node_counter = 0;

int main()
{
    for (int i = 1; i < 9; i++) {
        if (i % 2 == NULL)
            insert_node(i*2, FIRST);
        else
            insert_node(i, LAST);
    }

    print_linked_list();

    print_node(search_min());
    print_node(search_max());
    printf("sum: %d\n", summ_of_list());

    return 0;
}

/* ### BASIC FUNCTIONS ### */
node_t* create_node (int data)
{
    node_t * temp_node = (node_t*)malloc(sizeof(node_t));
    temp_node -> data = data;
    temp_node -> next = NULL;
    temp_node -> prev = NULL;
    return temp_node;
}

void insert_node(int data, enum insert_direction where)
{
    node_t *temp_node = create_node(data);

    // If the list is empty
    if (head == NULL) {
        head = temp_node;
        tail = temp_node;
        node_counter++;
        return;
    }

    if (where == FIRST) {
        temp_node -> next = head;
        head -> prev = temp_node;
        head = temp_node;
        node_counter++;

    } else if (where == LAST) {
        tail -> next = temp_node;
        temp_node -> prev = tail;
        tail = temp_node;
        node_counter++;

    } else {
        printf("Wrong insert_direction input.\n");
    }
}

node_t* search_node(int data)
{
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return NULL;
    }

    node_t *foward = head;
    node_t *backward = tail;

    for (int i = 0; i < (node_counter + 1) / 2; i++) {

        if (foward -> data == data)
            return foward;
        if (backward -> data == data)
            return backward;

        foward = foward -> next;
        backward = backward -> prev;
    }

    return NULL;
}

void remove_node(int data)
{
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    node_t *target_node = search_node(data);

    if (target_node == NULL) {
        printf("There is no %d node in list.\n", data);
        return;
    }

    // Only 1 node is in the list.
    if (head == tail) {
        free(head);
        node_counter--;
        return;
    }

    // If the target is the head.
    if (target_node == head) {
        (target_node -> next) -> prev = NULL;
        head = target_node -> next;
        free(target_node);
        node_counter--;
        return;
    }

    // If the target is the tail.
    if (target_node == tail) {
        (target_node -> prev) -> next = NULL;
        tail = target_node -> prev;
        free(target_node);
        node_counter--;
        return;
    }

    // If the target between two nodes.
    (target_node -> prev) -> next = target_node -> next;
    (target_node -> next) -> prev = target_node -> prev;
    free(target_node);
    node_counter--;
}

/* ### PRINT FUNCTIONS ### */
void print_linked_list()
{
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    node_t *ptr = head;

    while (ptr -> next != NULL) {
        printf("%d -><- ", ptr -> data);
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

    if (temp -> next != NULL && temp -> prev != NULL)
        printf("%d <- %d -> %d\n", (temp -> prev) -> data ,temp -> data, (temp -> next) ->data);
    else if (temp -> next != NULL && temp -> prev == NULL)
        printf("~ <- %d -> %d\n", temp -> data, (temp -> next) ->data);
    else if (temp -> next == NULL && temp -> prev != NULL)
         printf("%d <- %d -> ~\n", (temp -> prev) -> data,temp -> data);
    else
        printf("~ <- %d -> ~\n", temp -> data);
}

/* ### EXTRA FUNCTIONS ### */
node_t* search_min()
{
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    int min = head -> data;
    node_t* min_node = NULL;

    node_t *foward = head;
    node_t *backward = tail;

    for (int i = 0; i < (node_counter + 1) / 2; i++) {

        if (foward -> data < min) {
            min = foward -> data;
            min_node = foward;
        }

        if (backward -> data < min) {
            min = backward -> data;
            min_node = backward;
        }

        foward = foward -> next;
        backward = backward -> prev;
    }

    return min_node;
}

node_t* search_max()
{
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    int max = head -> data;
    node_t* max_node = NULL;

    node_t *foward = head;
    node_t *backward = tail;

    for (int i = 0; i < (node_counter + 1) / 2; i++) {

        if (foward -> data > max) {
            max = foward -> data;
            max_node = foward;
        }

        if (backward -> data > max) {
            max = backward -> data;
            max_node = backward;
        }

        foward = foward -> next;
        backward = backward -> prev;
    }

    return max_node;
}

int summ_of_list()
{
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    int sum = 0;
    node_t *foward = head;
    node_t *backward = tail;

    for (int i = 0; i < (node_counter + 1) / 2; i++) {
        sum += foward -> data;
        sum += backward -> data;

        foward = foward -> next;
        backward = backward -> prev;
    }

    // If there are odd elements the middle one counted two times, so we have to subtract it.
    if (node_counter % 2)
        sum -= foward -> data;

    return sum;
}











