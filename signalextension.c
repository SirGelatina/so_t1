#include "header.h"

SignalExtend extend;

void * function_signalextend(){
	sem_init(&extend.input_m, 0, 0);

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	extend.input = &IR.output_15_0;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		printf("Init extend\n");
		fflush(0);
		
		// DOWN nos sem_t da entrada
		sem_wait(&extend.input_m);

		int n = *extend.input;

		if(n & 1<<15)
			extend.output = n | 0xffff0000;
		else
			extend.output = n & 0x0000ffff;

		// UP nos sem_t de entrada das unidades que utilizam essas saidas
		sem_post(&shift_one.input_m);
		sem_post(&mux6.input_m[2]);

		printf("Ready extend\n");
		fflush(0);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Extensao de Sinal\n");
    fflush(0);

    pthread_exit(0);
}


