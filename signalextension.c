#include "header.h"

struct signalextend{
	int * input;

	mutex input_m;

	int output;
}

SignalExtend extend;

void function_signalextend(){
	extend.input = IR.output_15_0;

	pthread_barrier_wait(&clocksync);

	while(1){
		pthread_wait(&extend.input_m);

		int n = *extend.input;

		if(n & 1<<15)
			extend.output = n | 0xffff0000;
		else
			extend.output = n & 0x0000ffff;

		pthread_post(&shift_one.input_m);
		pthread_post(&mux6.input_m[2]);

		pthread_barrier_wait(&clocksync);
	}
}


