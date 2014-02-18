#include <stdio.h>
#include "threads.h"
#include <stdint.h>
#include <stdlib.h>

void other_function(void *arg){
    int i;
    for(i = 0; i < 6; i++){
        printf("Other thread counter: %d\n", i);
        thread_yield();
    }
}

void sum(void *arg){
	int *arr = (int *)arg;
	printf("Adding array of following values:\n%d %d %d %d\n", arr[1], arr[2], arr[3], arr[4]);

	int i;
	int sum = 0;
	for(i = 1; i < arr[0]; i++){
		sum += arr[i];
		printf("Sum so far: %d\n", sum);
		thread_yield();
	}
}

int main(int argc, char **argv)
{
    struct thread *other_thread = thread_create(other_function, NULL);
    thread_add_runqueue(other_thread);

    int *ptr;
	ptr = (int *) malloc(5 * sizeof(int));

	ptr[0] = 5;
	ptr[1] = 110;
	ptr[2] = 222;
	ptr[3] = 333;
	ptr[4] = 444;

    struct thread *add_thread = thread_create(sum, ptr);
    thread_add_runqueue(add_thread);

	thread_start_threading();
    printf("FINISH\n");
    return 0;
}
