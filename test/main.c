#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "threads.h"

void f2(void*);
void f3(void*);
void f4(void*);

void f1(void* arg){
    printf("f1\n");
    printf("creating thread 2 in f1\n");
    struct thread *t2 = thread_create(f2, NULL);
    thread_add_runqueue(t2);
    printf("yielding in f1\n");
    thread_yield();
    printf("finishing f1 after yield\n");
}

void f2(void* arg){
    printf("f2\n");
    printf("creating thread 3 in f2\n");
    struct thread *t3 = thread_create(f3, NULL);
    thread_add_runqueue(t3);    
    printf("yielding in f2\n");    
    thread_yield();
    printf("finishing f2 after yield\n");

    //thread_exit();
}

void f3(void* arg){
    printf("f3\n");
    printf("creating thread 4 in f3\n");    
    struct thread *t4 = thread_create(f4, NULL);
    thread_add_runqueue(t4);   
    printf("yielding in f3\n");
    thread_yield();
    printf("finishing f3 after yield\n");
}

void f4(void* arg){
    printf("f4\n");
}

int main(int argc, char **argv)
{
    printf("creating thread 1 in main\n");
    struct thread *t1 = thread_create(f1, NULL);
    thread_add_runqueue(t1);
  
    printf("***** start threading *****\n");
    thread_start_threading();
    printf("\nexited\n");
    return 0;
}