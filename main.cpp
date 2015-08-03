/*Daniel Cheng - dyc8av
Written February 18, 2015
This is where the thread function and struct is declared
along with the main() function. A global barrier is created
and used by all threads for synchronization */

#include <iostream>
#include "barrier.h"
#include <stdio.h>
#include <sstream>
#include <pthread.h>
#include <vector>
#include <math.h>
using namespace std;

Barrier barrier; /*Create global Barrier*/
vector<int> globalvector; /*Create global vector for threads to manipulate to find max value*/
int rounds; /*The number of rounds each thread will run*/

/*Data that is passed to each thread*/
struct array_data {
	int max; /*The max value that will be written to globalvector*/
	int firstpos; /*The first value to compare*/
	int secondpos; /*The second value to compare*/
	int index; /*The current index of the thread in tids*/
};

/*Calculate the max between two values and replace in global vector*/
void *max(void *arg) {
	array_data *mydata = (array_data *) arg; /*cast data*/
	for(int i = 0; i < rounds; i++) {
		barrier.wait(); /*WAIT - ensure threads are correctly concurent*/
		/*find max*/
		if(globalvector.at(mydata->firstpos) > globalvector.at(mydata->secondpos)) {
			mydata->max = globalvector.at(mydata->firstpos);
		}
		else if(globalvector.at(mydata->firstpos) < globalvector.at(mydata->secondpos)) {
			mydata->max = globalvector.at(mydata->secondpos);
		}
		else {
			mydata->max = globalvector.at(mydata->firstpos);
		}
		/*modify global array with max*/
		globalvector.at(mydata->index) = mydata->max;
	}
}

int main() {
	/*Read input from stdin*/
	int N = 0;
	string line;
	int num;
	while(getline(cin,line)) {
		if(line.empty()) {
			break; /*stop reading if empty line*/
		}
		stringstream stream(line);
		stream >> num; /*convert string to int*/
		globalvector.push_back(num); /*add into to global vector*/
		N++; 
	}

	/*Initialize the barrier*/
	barrier.barrier_init(N/2); 
	/*Calculate the number of rounds per thread*/
	rounds = log2(N);

	pthread_t tids[N/2]; /*array of thread id*/
	array_data args[N/2]; /*array of data passed to max for each thread*/
	pthread_attr_t attr;
	pthread_attr_init(&attr); /*initialize default attribute*/


	for(int i = 0; i < N/2; i++) {
		args[i].firstpos = (i*2); /*first value to max*/
		args[i].secondpos = ((i*2)+1); /*second value to max*/
		args[i].index = i; /*index of the thread*/
		pthread_create(&tids[i],&attr,max,(void*)&args[i]);
	}

	/*join the threads to ensure that all complete before main exits*/
	for(int i = 0; i < N/2; i++) {
		pthread_join(tids[i],NULL);
	}

	/*Print out maximum value to stdout*/
	cout << globalvector.at(0) << endl; 

	/*Exit the threads*/
	pthread_exit(NULL);

	/*return*/
	return 0;
}