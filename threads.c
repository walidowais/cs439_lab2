#include <stdio.h>
#include <threads.h> 

struct thread{
	//Some notes to add: size is the difference between the stack pointer and the base pointer 
	uintptr_t* stack; //Points to the stack 
	uintptr_t* base_pointer; //Points to bottom of stack or however the fuck we're implementing it 
 	uintptr_t* stack_pointer; //Points to where we currently are on stack 
 	void (*function_pointer)(void *); //Points to function we're supposed to run 

	//Allocates an initial stack with 4096 slots 
	stack = (uni_ptr_t*)malloc(sizeof(uintptr_t) * 4096);
}

struct thread *thread_create(void (*f)(void *arg), void *arg){

}

void thread_add_runqueue(struct thread *t){

}

void thread_yield(void){

}

void dispatch(void){

}

void schedule(void){

}

void thread_exit(void){

}


void thread_start_threading(void){

}



