#include <stdio.h>
#include <threads.h> 

struct thread{
	uintptr_t* stack;
	uintptr_t* base_pointer;
 	uintptr_t* stack_pointer;

	//Allocates an initial with 4096 slots 
	stack = (uni_ptr_t*)malloc(sizeof(uintptr_t) * 4096);

}