#include "header.h"

struct concatenator{
	int * input_pc;
	int * input_shift;

	mutex input_pc_m;
	mutex input_shift_m;

	int output;
}

Concatenator jumpconcat;

void function_concatenator(){
	pthread_barrier_wait(&clocksync);

	while(1){
		sem_wait(jumpconcat.input_m);
		sem_wait(jumpconcat.input_shift_m);

		jumpconcat.output = 

		pthread_barrier_wait(&clocksync);
	}
}