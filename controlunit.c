#include "header.h"

struct controlunit{
	int * output_5_0;

	int ControlBits;
}

ControlUnit controlunit;

void function_controlunit(){
	

	pthread_barrier_wait(&clocksync);

	while(1){
		
		pthread_barrier_wait(&clocksync);
	}
}