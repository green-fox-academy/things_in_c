/*
    ##########################
    ### DYNAMIC HASH TABLE ###
    ##########################
    ###       By Marci     ###
    ##########################

    The good point in this solution is the size of the table is not fix.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Typedef
typedef struct node{
    int data;
    int key;
}node_t;

// Global variables
node_t **hash_array;    // This array holds pointers to the nodes. ( its same as : *hash_array[] )
node_t *deleted_item;   // This pointer will point to a deleted items
int memory_size = 0;
int num_of_items = 0;

// Basic functions
int insert_item(int key, int data);
node_t* search_item(int key);
int hash_code(int key);
int delete_item(node_t *item);
int check_memory_size();
int create_hash_memory(int size);

// Print functions
int display_table();
void print_item(node_t *item);


int main()
{
    deleted_item = (node_t*) malloc(sizeof(node_t));
    deleted_item -> data = -1;
    deleted_item -> key = -1;

    for (int i = 0; i <= 10; i++) {
        insert_item(i, i*7);
    }

    delete_item(search_item(3));

    display_table();

    if (insert_item(2, 100))
        printf("cant make it.\n");

    delete_item(search_item(4));

    display_table();

    return 0;
}

/*  Name:       hash_code
*   Purpose:    Makes an index from the key
*   Inputs:     int key - This must be individual number for all the elements
*   Output:     int hash_index
*/
int hash_code(int key)
{
    return (key % memory_size);
}

/*  Name:       insert_item
*   Purpose:    Creates a node_t item dynamically and puts it in the hash memory
                If the memory is 0 it creates the memory.
                Finds a place for the item in the memory.
                    If the memory is full or doesn't exist it allocates a bigger one and puts the item at the end of it.
                    It tries to put the item in the index-th place if it isn't possible then tries to put it to the next place etc...
*   Inputs:     int key - individual key, int data - this is the data.
*   Output:     0 - if it was inserted, 1 - If there is an item with the same key.
*/
int insert_item(int key, int data)
{
    // If an item exist with the same key.
    if (search_item(key) != NULL)
        return 1;

    num_of_items++;

    // Make the new item dynamically
    node_t *item = (node_t*)malloc(sizeof(node_t));
    item -> data = data;
    item -> key = key;

    // If the memory is full or is empty this puts the new node at the end of it.
    if (check_memory_size()) {
        hash_array[num_of_items - 1] = item;
        return 0;
    }

    // Get hash code
    int hash_index = hash_code(key);

    // Move array until empty slot or deleted cell
    while (hash_array[hash_index] != NULL && hash_array[hash_index] -> key != -1) {
        hash_index++;
        hash_index = hash_code(hash_index);
    }

    hash_array[hash_index] = item;
    return 0;
}

/*  Name:       search_item
*   Purpose:    searches a node_t item in the memory.
                    If the memory is empty or doesnt't exists
                    or the item isn't in the memory it returns with a NULL pointer.
*   Inputs:     int key - individual key
*   Output:     node_t* - pointer to the searched item
*/
node_t* search_item(int key)
{
     // If the memory doesn't exist or it's empty.
    if (memory_size == 0 || num_of_items == 0)
        return NULL;

    // Counter for the while loop. This will cause return if the searched item doesn't exist.
    int counter = 0;

    // Make hash index
    int hash_index = hash_code(key);

    // Moove in array until an empty
    while (hash_array[hash_index] != 0) {

        if ( hash_array[hash_index] -> key == key)
            return hash_array[hash_index];

        counter++;
        if (counter == memory_size)
            return NULL;

        hash_index++;
        hash_index = hash_code(hash_index);
    }
}

/*  Name:       delete_item
*   Purpose:    Delete the target node_t item.
*   Inputs:     node_t* item - This is the target to be deleted
                    If it's in the memory delete it from there, and replace it with a deleted_item pointer.
*   Output:     0 - if it was deleted, 1 -  if it wasn't deleted.
*/
int delete_item(node_t *item)
{
    if (item == NULL)
        return 1;

    int key = item -> key;

    int hash_index = hash_code(key);

    while (hash_array[hash_index] != NULL) {

        if (hash_array[hash_index] -> key == key) {
            free(hash_array[hash_index]);
            hash_array[hash_index] = deleted_item;
            num_of_items--;
            return 0;
        }

        hash_index++;
        hash_index = hash_code(hash_index);
    }

    return 1;
}

/*  Name:       create_hash_memory
*   Purpose:    To create a memory pool for the items.
*   Inputs:     int size - no explanation needed for this :)
*   Output:     0 - if the memory was made, 1 - if the memory already exists.
*/
int create_hash_memory(int size)
{
    // If the memory already exists.
    if (memory_size)
        return 1;

    hash_array = (node_t**)calloc(size, sizeof(node_t*));

    // Fill the memory with NULL pointers.
    for (int i = 0; i < size; i++) {
        hash_array[i] = NULL;
    }

    memory_size = size;
}

/*  Name:       check_memory_size
*   Purpose:    If the number of elements is bigger than the current memory size its allocate a bigger memory
*   Inputs:     Nothing (It works with global variables)
*   Output:     1 If needed to make a bigger memory
*               0 If the number of elements was lower than the size of array
*/
int check_memory_size()
{
    if (memory_size == 0) {
        create_hash_memory(1);
    }

    if (num_of_items > memory_size){

        hash_array = (node_t**)realloc(hash_array, num_of_items * sizeof(node_t*));

        for (int i = memory_size; i < num_of_items; i++) {
            hash_array[i] = NULL;
        }

        memory_size = num_of_items;

        return 1;
    }

    return 0;
}


// Print functions:

/*  Name:       print_item
*   Purpose:    Print out the key and the data of an item.
*   Inputs:     node_t *item - Target item to be printed.
*   Output:     Nothing.
*/
void print_item(node_t *item)
{
    if (item == NULL) {
        printf("(~,~) ");

    } else {
        printf("(%d,%d) ", item -> key, item -> data);
    }
}

/*  Name:       display_table
*   Purpose:    Print all items, deleted_items, NULL pointers
*   Inputs:     Nothing (It works with global variables)
*   Output:     0 - If it was printed well, 1 - If the memory doesn't exists.
*/
int display_table()
{
    if (!memory_size)
        return 1;

    printf("memory size: %d, items: %d, free spaces: %d\n", memory_size, num_of_items, memory_size - num_of_items);

    for (int i = 0; i < memory_size; i++) {

        print_item(hash_array[i]);

    }

    printf("\n\n");
    return 0;
}