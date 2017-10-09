#include <stdio.h>
#include <stdlib.h>

void clear_memory(int *mem_ptr, int mem_len);
void print_memory(int *mem_ptr, int mem_len);

int fibo_iterative(int n);
int fibo_recursive(int n);
int fibo_memorized(int *mem_ptr, int n);
int fibo_dynamic_memo(int n);

int *memory_dynamic;
int mem_din_len = 0;


int main()
{

    int n = 42;

    // ################## ITERATIVE #######################

    printf("Fibonacci iterative: \n");

    for (int i = 1; i <= n; i++) {
        printf("ite[%d]: \t%d \n", i, fibo_iterative(i));
    }
    printf("\n");

    // ################## RECURSIVE #######################

    printf("Fibonacci recursive: \n");

    for (int i = 1; i <= n; i++) {
        printf("recur[%d]:\t%d\n", i,  fibo_recursive(i));
    }

    printf("\n");

    // ################## MEMORIZED #######################

    int memory_length = n;
    int memory[memory_length];

    clear_memory(memory, memory_length);

    printf("Fibonacci memorized: \n");

    for (int i = 1; i <= n; i++) {
        printf("memo[%d]:\t%d\n", i,  fibo_memorized(memory, i));
    }

    printf("\n");

    // ################## DYNAMIC MEMORIZED #######################

    printf("Fibonacci dynamically memorized\n\n");

    // number = n+1-th Fibonacci number, the memo array will contain numbers until the n element.
    int number = fibo_dynamic_memo(n);
    print_memory(memory_dynamic, mem_din_len);
    printf("din_mem[%d]: \t%d\n", n + 1, number);

    return 0;
}

int fibo_iterative(int n)
{

    int fibo = 1;
    int memo1 = 1;
    int memo2 = 1;

    if (n <= 2)
        return fibo;

    for (int i = 2; i < n; i++) {
        fibo = memo1 + memo2;
        memo2 = memo1;
        memo1 = fibo;
    }

    return fibo;
}

int fibo_recursive(int n)
{
    if (n <= 2)
        return 1;

    return fibo_recursive(n - 2) + fibo_recursive(n - 1);
}

int fibo_memorized(int *mem_ptr, int n)
{
    if (n <= 2)
        return 1;

    if (mem_ptr[n - 1] == 0)
        mem_ptr[n - 1] = fibo_memorized(mem_ptr, n - 1);

    if (mem_ptr[n - 2] == 0)
        mem_ptr[n - 2] = fibo_memorized(mem_ptr, n - 2);

    return mem_ptr[n - 2] + mem_ptr[n - 1];
}

int fibo_dynamic_memo(int n)
{
    if (n > mem_din_len) {
        int *temp_memo = (int*)calloc(n, sizeof(int));

        for (int i = 0; i < n; i++) {
            if (i < mem_din_len)
                temp_memo[i] = memory_dynamic[i];
            else
                temp_memo[i] = 0;
        }

        memory_dynamic = temp_memo;
        mem_din_len = n;
    }

    if (n <= 1) {
      memory_dynamic[n] = 1;
      return 1;
    }


    if (memory_dynamic[n - 1] == 0)
        memory_dynamic[n - 1] = fibo_dynamic_memo(n - 1);

    if (memory_dynamic[n - 2] == 0)
        memory_dynamic[n - 2] = fibo_dynamic_memo(n - 2);

    return memory_dynamic[n - 2] + memory_dynamic[n - 1];
}


// Memory functions
void clear_memory(int *mem_ptr, int mem_len)
{
    for (int i = 0; i < mem_len; i++) {
        mem_ptr[i] = 0;
    }
}

void print_memory(int *mem_ptr, int mem_len)
{
    for (int i = 0; i < mem_len; i++) {
        printf("din_mem[%d]: \t%d\n", i + 1, mem_ptr[i]);
    }
}









