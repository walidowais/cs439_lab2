#include <stdio.h>
#include <threads.h> 

struct thread{
	uni_ptr_t* stack;

	//Allocates an initial with 4096 slots 
	stack = (uni_ptr_t*)malloc(sizeof(uni_ptr_t) * 4096);
}