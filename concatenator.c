#include "header.h"

struct concatenator{
	int * input_pc;
	int * input_shift;

	pthread_mutex_t input_pc_m;
	pthread_mutex_t input_shift_m;

	int output;
}

Concatenator jumpconcat;

void function_concatenator(){
	jumpconcat.input_pc = &PC.output;
	jumpconcat.input_shift = &shift_two.output;

	pthread_barrier_wait(&clocksync);

	while(1){
		pthread_mutex_lock(jumpconcat.input_pc_m);
		pthread_mutex_lock(jumpconcat.input_shift_m);

		jumpconcat.output = (*jumpconcat.input_pc & 0xf0000000) | (*jumpconcat.input_shift & 0x0fffffff);

		pthread_mutex_unlock(&mux5.input_m[2]);

		pthread_barrier_wait(&clocksync);
	}
}