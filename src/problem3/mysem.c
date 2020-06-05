#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


typedef struct {
	int sema;
	cond_t cond;
	mutex_t mu;
} mysem_t ;


void
mysem_init (mysem_t * sem, int init)
{
	Pthread_mutex_lock(&sem.mu);
	sem.sema = init;
	Pthread_mutex_unlock(&sem.mu);
}

void
mysem_post (mysem_t * sem)
{
	Pthread_mutex_lock(&sem.mu);
	sem.sema++;
	if(sem.sema==0)
		Pthread_cond_signal(&sem.cond);
	Pthread_mutex_unlock(&sem.mu);

}

void
mysem_wait (mysem_t * sem)
{
	Pthread_mutex_lock(&sem.mu);
	sem.sema--;
	if(sem.sema<0)
		Pthread_cond_wait(&sem.cond, &sem.mu);
	Pthread_mutex_unlock(&sem.mu);

}
