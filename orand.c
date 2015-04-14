#include "header.h"

typedef struct or_and{

	// Input
	int *zero;
	int *PCWriteCond, *PCWrite;

	// Output
	int output;

	// Semaforos
	mutex zero_m;

}Or_and;

Or_and OR_AND;

void function_or_and(){

	OR_AND.zero = &ALU.output_alu_zero;

	sem_wait(&OR_AND.zero_m);

	pthread_barrier_wait(&clocksync);

	while(1){

		if (controlunit.ControlBits & separa_PCWriteCond == 0) OR_AND.PCWriteCond = 0;
		else OR_AND.PCWriteCond = 1;

		if (controlunit.ControlBits & separa_PCWrite == 0) OR_AND.PCWrite = 0;
		else OR_AND.PCWrite = 1;

		OR_AND.output = (OR_AND.zero & OR_AND.PCWriteCond) | OR_AND.PCWrite;

		sem_post(&PC.SC);

		pthread_barrier_wait(&clocksync);

	}

}

