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

	fprintf(stderr, "\tthread_create\n");

	struct thread *new_thread = malloc(sizeof(struct thread));

	new_thread->function = f;
	new_thread->arguments = arg;

	int pma_test = posix_memalign((void **)&(new_thread->stack), 8, (sizeof(uintptr_t) * 4096));
	if(pma_test){
		fprintf(stderr, "\t\tThere was an error with posix_memalign()\n");
		exit(1);
	}

	new_thread->esp = new_thread->stack;
	new_thread->ebp = new_thread->stack;

	new_thread->init = 0;
	new_thread->set = 0;

}


void thread_add_runqueue(struct thread *t){

	fprintf(stderr, "\tthread_add_runqueue\n");

	if(!root){
		root = malloc(sizeof(struct node));
		last = root;
	}
	else{
		last->next = malloc(sizeof(struct node));
		last = last->next;
	}

	last->thread_ptr = t;

}


void thread_start_threading(void){
	
	fprintf(stderr, "\tthread_start_threading\n");

	schedule();
	dispatch();

}


void schedule(void){

	fprintf(stderr, "\tschedule\n");

	last_thread = current_thread;

	if(root){
		struct node *temp = root;
		root = root->next;
		current_thread = temp->thread_ptr;
		free(temp);
	}
	else{
		fprintf(stderr, "\t\tNothing to schedule\n");
		exit(1);
	}

}


void dispatch(void){

	fprintf(stderr, "\tdispatch\n");

	if(last_thread){
		__asm__ volatile("mov %%rsp, %%rax" : "=a" (last_thread->esp) : );
		__asm__ volatile("mov %%rbp, %%rax" : "=a" (last_thread->ebp) : );
	}

	__asm__ volatile("mov %%rax, %%rsp" : : "a" (current_thread->esp) );
	__asm__ volatile("mov %%rax, %%rbp" : : "a" (current_thread->ebp) );

	if(!current_thread->init){
		current_thread->init = 1;
		current_thread->function(current_thread->arguments);
	}
	else{
		longjmp(current_thread->env, 1);
	}

	thread_exit();

}


void thread_yield(void){

	fprintf(stderr, "\tthread_yield\n");

	int x = 0;
	x = setjmp(current_thread->env);
	if(!x){
		x=0;
		thread_add_runqueue(current_thread);
		schedule();
		dispatch();
	}

}


void thread_exit(void){

	fprintf(stderr, "\tthread_exit\n");

	free(current_thread->stack);
	free(current_thread);

	schedule();
	dispatch();

}