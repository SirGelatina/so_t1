#include "header.h"

typedef struct or_and{

	int *input1, *input2;
	int output;

}Or_and;

/*
Functions parameters: 
	flag = 0 -> OR 
	flag = 1 -> AND 
*/
void function_or_and(int flag){

	or->input1 = ;
	or->input2 = &and.output;

	and->input1 = ;
	and->input2 = ;

	pthread_barrier_wait(&clocksync);

	while(1){

		if (flag == 0) or->output = *or->input1 | *or->input2;
		else and->output = *and->input1 & *and->input2; 

		pthread_barrier_wait(&clocksync);

	}

}

