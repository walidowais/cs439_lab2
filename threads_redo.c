#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <setjmp.h>
#include "threads.h"


struct node *root;
struct node *last;


struct node
{
	struct thread *thread_ptr;
	struct node *next;
};


struct thread *last_thread;
struct thread *current_thread;


struct thread
{
	void (*function)(void*);
	void *arguments;

	uintptr_t *stack;
	uintptr_t *esp;
	uintptr_t *ebp;

	jmp_buf env;
	int init;
	int set;
};


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

