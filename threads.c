#include <stdio.h>
#include "threads.h" 
#include <stdint.h> 
#include <stdlib.h>

/*

For saving the values into registers 
Used along with setjmp; saves the registers 
__asm__ volatile("mov %%rsp, %%rax" : "=a" (last_thread->esp) : );
__asm__ volatile("mov %%rbp, %%rax" : "=a" (last_thread->ebp) : );


Used along with longjmp because you want to load back the registers 
For loading the values back into the current stack pointer & base pointer 
__asm__ volatile("mov %%rax, %%rsp" : : "a" (current_thread->esp) );
__asm__ volatile("mov %%rax, %%rbp" : : "a" (current_thread->ebp) );

*/

struct thread{
	//Some notes to add: size is the difference between the stack pointer and the base pointer 
	uintptr_t* stack; //Points to the stack 
	uintptr_t* base_pointer; //Points to bottom of stack or however the fuck we're implementing it 
 	uintptr_t* stack_pointer; //Points to where we currently are on stack 
 	void (*function_pointer)(void *); //Points to function we're supposed to run 
 	void *parameters;

};

// Queue stuff
struct node{
	struct thread *current;
	struct node *next;
};

struct node *root;
struct node *last;

/*	Returns a pointer to a thread  
	Accepts a function into the argument f (pointer to the function)
	arg becomes the function's arguments
*/ 
struct thread *thread_create(void (*f)(void *arg), void *arg){

	struct thread *thread_pointer = malloc(sizeof(struct thread));

	int test = posix_memalign((void **)&(thread_pointer->stack), 8, (sizeof(uintptr_t)) * 4096);

	if(test){
		fprintf(stderr, "Error with posix_memalign()\n");
		exit(1);
	}

	thread_pointer -> stack_pointer = thread_pointer -> stack;
	thread_pointer -> base_pointer = thread_pointer -> stack_pointer;

	thread_pointer -> function_pointer = f;
	thread_pointer -> parameters = arg;

	return thread_pointer;

}

void thread_add_runqueue(struct thread *t){
	if(!root){
		root = malloc(sizeof(struct node));
		last = root;
	}
	else{
		last->next = malloc(sizeof(struct node));
		last = last->next;
	}

	last->current = t;
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



