#include <stdio.h>
#include "threads.h" 
#include <stdint.h> 
#include <stdlib.h>
#include <setjmp.h>

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

int exit_count = 0;

struct thread{
	//Some notes to add: size is the difference between the stack pointer and the base pointer 
	uintptr_t* stack; //Points to the stack 
	uintptr_t* base_pointer; //Points to bottom of stack or however the fuck we're implementing it 
 	uintptr_t* stack_pointer; //Points to where we currently are on stack 
 	void (*function_pointer)(void *); //Points to function we're supposed to run 
 	void *parameters;
 	jmp_buf saved_state;
 	int state_set;

};

struct thread *current_thread;
struct thread *last_thread;

// Queue stuff
struct node{
	struct thread *node_thread;
	struct node *next;
};

struct node *root_node;
struct node *last_node;

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
	if(!root_node){
		root_node = malloc(sizeof(struct node));
		last_node = root_node;
	}
	else{
		last_node->next = malloc(sizeof(struct node));
		last_node = last_node->next;
	}

	last_node->node_thread = t;
}

void thread_yield(void){
	// __asm__ volatile("mov %%rsp, %%rax" : "=a" (last_thread->stack_pointer) : );
	// __asm__ volatile("mov %%rbp, %%rax" : "=a" (last_thread->base_pointer) : );
	// current_thread->state_set = 1;
	// setjmp(current_thread->saved_state);

	exit_count++;
	if(exit_count > 10){
		exit(1);
	}

	thread_add_runqueue(current_thread);
	schedule();
	dispatch();
}

void dispatch(void){
	
	if(last_thread){
		// save state for last thread
		__asm__ volatile("mov %%rsp, %%rax" : "=a" (last_thread->stack_pointer) : );
		__asm__ volatile("mov %%rbp, %%rax" : "=a" (last_thread->base_pointer) : );
		last_thread->state_set = 1;
		setjmp(last_thread->saved_state);
	}

	if(current_thread->state_set){
		// restore state of current thread
		current_thread->state_set = 0;
		longjmp(current_thread->saved_state, 9);
		__asm__ volatile("mov %%rax, %%rsp" : : "a" (current_thread->stack_pointer) );
		__asm__ volatile("mov %%rax, %%rbp" : : "a" (current_thread->base_pointer) );
	}
	else{
		current_thread->function_pointer(current_thread->parameters);
	}

	thread_exit();

}

void schedule(void){
	last_thread = current_thread;

	struct node *temp = root_node;
	root_node = root_node->next;
	current_thread = temp->node_thread;

	free(temp);
}

void thread_exit(void){
	free(current_thread->stack);
	free(current_thread);
}


void thread_start_threading(void){
	schedule();
	dispatch();
}

