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

struct thread *root; 
struct thread *last;	 


struct thread{
	//Some notes to add: size is the difference between the stack pointer and the base pointer 
	uintptr_t* stack; //Points to the stack 
	uintptr_t* base_pointer; //Points to bottom of stack or however the fuck we're implementing it 
 	uintptr_t* stack_pointer; //Points to where we currently are on stack 
 	void (*function_pointer)(void *); //Points to function we're supposed to run 
 	struct thread *next; //Next thread in the list 

	//Allocates an initial stack with 4096 slots 
	// stack = (uni_ptr_t*)malloc(sizeof(uintptr_t) * 4096);
};

/*	Returns a pointer to a thread  
	Accepts a function into the argument f (pointer to the function)
	arg becomes the function's arguments
*/ 
struct thread *thread_create(void (*f)(void *arg), void *arg){
	// printf("hello world!\n");
	// if(root == 0){
	// 	root = malloc(sizeof(struct thread));
	// 	last = root;
	// 	root->function_pointer = f(arg);   
	// 	return root;
	// }

	// else{
	// 	last->next = malloc(sizeof(struct thread));
	// 	last = last->next;
	// 	last->function_pointer = f(arg); 
	// 	return last; 
	// } 
	struct thread *thread_pointer = malloc(sizeof(struct thread));
	thread_pointer -> stack = malloc(sizeof(uintptr_t) * 4096);
	return thread_pointer;

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



