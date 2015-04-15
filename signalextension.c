#include "header.h"

struct signalextend{

	// Input
	int * input;

	// Output
	int output;

	// Mutex
	mutex input_m;
}

SignalExtend extend;

void function_signalextend(){

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	extend.input = &IR.output_15_0;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(1){
		
		// DOWN nos mutex da entrada
		sem_wait(&extend.input_m);

		int n = *extend.input;

		if(n & 1<<15)
			extend.output = n | 0xffff0000;
		else
			extend.output = n & 0x0000ffff;

		// UP nos mutex de entrada das unidades que utilizam essas saidas
		sem_post(&shift_one.input_m);
		sem_post(&mux6.input_m[2]);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}
}


