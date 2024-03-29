#ifndef THREADS_H_
#define THREADS_H_

struct thread;
struct thread *thread_create(void (*f)(void *arg), void *arg);
void thread_add_runqueue(struct thread *t);
void thread_yield(void);
void dispatch(void);
void schedule(void);
void thread_exit(void);
void thread_start_threading(void);
#endif // THREADS_H