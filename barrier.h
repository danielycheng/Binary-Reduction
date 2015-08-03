/*Daniel Cheng - dyc8av
Written February 18, 2015
The purpose of barrier.h is to define the structure of an
implementation of the Barrier class, which will be used to
run concurrent threads.*/

#ifndef BARRIER_H
#define BARRIER_H
#include <semaphore.h> 
using namespace std;

class Barrier {
public:
	Barrier(); /*Default constructor*/
	void barrier_init(int n); /*Initializes all variables and semaphores as binary semaphores*/
	void wait(); /*Will wait until wait() has been called size times*/

private:
	int size; /*The amount of times wait() must be called in order to continue*/
	int count; /*The current number of times wait() has been called*/
	sem_t mutex; /*Binary semaphore to guarentee mutual exclusion*/
	sem_t waitq; /*Binary semaphore to add waiting threads to a queue*/
	sem_t throttle; /*Binary semaphores to guarentee proper removal from the waitq*/
};
#endif