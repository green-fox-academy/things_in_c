#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MEM_MULTIPLIER 2

typedef struct dat {
    int data_int;
    char data_str[50];
    uint32_t ID;
}data_t;

typedef struct mem {
    data_t **ptr_arr;
    size_t arr_size;
    int used;
}memory_t;

// Funcitons
memory_t* create_memory(size_t size);
data_t* create_data(int data_int, char* data_str, uint32_t ID);
int memory_size_check(memory_t *mem);
int generate_index(memory_t *memory, uint32_t ID);
int insert_data(memory_t *memory, data_t *data);
void print_memory(memory_t *memory);
data_t* search_data(memory_t *memory, uint32_t ID);
int remove_data(memory_t *memory, uint32_t ID);
int print_data(data_t *data);

int main()
{
    memory_t *memory = create_memory(4);

    data_t *temp_data;

    temp_data = create_data(123, "Im data", 23);

    insert_data(memory, temp_data);

    print_memory(memory);

    remove_data(memory, 23);

    printf("\n");

    print_memory(memory);

    return 0;
}

memory_t* create_memory(size_t size)
{
    if (size == 0)
        return NULL;

    data_t **temp_arr = (data_t**)calloc(size, sizeof(data_t*));

    for (int i = 0; i < size; i++) {
        temp_arr[i] = NULL;
    }

    memory_t *temp_mem = (memory_t*)malloc(sizeof(memory_t));

    temp_mem -> arr_size = size;
    temp_mem -> ptr_arr = temp_arr;
}

data_t* create_data(int data_int, char* data_str, uint32_t ID)
{
    data_t* temp_data = (data_t*)malloc(sizeof(data_t));

    temp_data -> data_int = data_int;
    strcpy(temp_data -> data_str, data_str);
    temp_data -> ID = ID;

    return temp_data;
}

int generate_index(memory_t *memory, uint32_t ID)
{
    if (memory == NULL)
        return -1;

    return (ID % (memory -> arr_size));
}

int insert_data(memory_t *memory, data_t *data)
{
    if (memory == NULL)
        return -1;

    if (data == NULL)
        return -2;

    if (memory_size_check(memory))
        return -3;

    int index = generate_index(memory, data -> ID);

    if (index == -1)
        return -4;

    while (1) {
        if ((memory -> ptr_arr)[index] == NULL) {
            (memory -> ptr_arr)[index] = data;
            break;
        }

        if (index == memory -> arr_size)
            index = 0;
        else
            index++;
    }

    memory -> used++;
    return 0;
}

data_t* search_data(memory_t *memory, uint32_t ID)
{
    if (memory == NULL || memory -> arr_size == 0)
        return NULL;

    int index = generate_index(memory, ID);
    int counter = 1;

    while (1) {

        if ((memory -> ptr_arr)[index] -> ID == ID) {
            return (memory -> ptr_arr)[index];
        }

        if (index == memory -> arr_size)
            index = 0;
        else
            index++;

        if (counter == memory -> arr_size)
            return NULL;
        else
            counter++;
    }
}


int remove_data(memory_t *memory, uint32_t ID)
{
    if (memory == NULL)
        return -1;

    if (memory -> arr_size == 0)
        return -2;

    int index = generate_index(memory, ID);
    int counter = 1;

    while (1) {

        if ((memory -> ptr_arr)[index] -> ID == ID) {
            free((memory -> ptr_arr)[index]);
            (memory -> ptr_arr)[index] = NULL;
            memory -> used--;
            return 0;
        }

        if (index == memory -> arr_size)
            index = 0;
        else
            index++;

        if (counter == memory -> arr_size)
            return -3;
        else
            counter++;
    }
}

int memory_size_check(memory_t *mem)
{
	if (mem == NULL)
		return -1;

	if (mem -> arr_size == 0)
		return -2;

	// Create bigger memory for hold the data
	if (mem -> used == mem -> arr_size) {

		data_t **new_ptr_arr = (data_t**)calloc((mem -> arr_size) * MEM_MULTIPLIER, sizeof(data_t*));

		for (int i = 0; i < mem -> arr_size; i++) {
			new_ptr_arr[i] -> data_int = (mem -> ptr_arr)[i] -> data_int;
			strcpy(new_ptr_arr[i] -> data_str, (mem -> ptr_arr)[i] -> data_str);
			new_ptr_arr[i] -> ID = (mem -> ptr_arr)[i] -> ID;
		}

		for (int i = mem -> arr_size; i < (mem -> arr_size) * MEM_MULTIPLIER; i++) {
            new_ptr_arr[i] = NULL;
		}

		free(mem -> ptr_arr);

		mem -> arr_size *= MEM_MULTIPLIER;
		mem -> ptr_arr = new_ptr_arr;
		return -3;
	}

	return 0;
}

void print_memory(memory_t *memory)
{
    for (int i = 0; i < memory -> arr_size; i++) {
        printf("%d: \t", i);
        print_data((memory -> ptr_arr)[i]);
    }
}

int print_data(data_t *data)
{
    if (data == NULL)
         printf("  ### NULL ###\n");
    else
        printf("int:%d  \tstr: %s\tID:%d\n", data -> data_int,
                                                    data -> data_str,
                                                    data -> ID);
}