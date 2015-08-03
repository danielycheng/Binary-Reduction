/*Daniel Cheng - dyc8av
February 18, 2015
The purpose of this class is to implement barrier.h. Three
functions are implemented: the default constructor, an initializing
function, and the wait function. */

#include <iostream>
#include "barrier.h"
#include <semaphore.h>
using namespace std;

/*Default constructor*/
Barrier::Barrier() {
}

/*Initializes the size of Barrier and sets mutex, waitq, and throttle as binary semaphores*/
void Barrier::barrier_init(int n) {
	size = n;
	count = 0;
	sem_init(&mutex,0,1);
	sem_init(&waitq,0,0); 
	sem_init(&throttle,0,0); 
}

/*Implementation of the wait() functionality*/
void Barrier::wait() {
	sem_wait(&mutex); /*take a mutex*/
	count++; /*Increment number of times wait() is called*/

	/*add thread to waitq if barrier is not met*/
	if(count < size) { 
		sem_post(&mutex); /*release mutex*/
		sem_wait(&waitq); /*add to waitq*/
		sem_post(&throttle); /*signal the throttle*/
	}
	/*If the barrier has been met, will remove threads from waitq*/
	else {
		for(int i = 0; i < size-1; i++) {
			sem_post(&waitq); /*release from waitq*/
			sem_wait(&throttle); /*wait for the throttle*/
		}
		count = 0; /*reset the barrier count*/
		sem_post(&mutex); /*release mutex*/
	}
}
