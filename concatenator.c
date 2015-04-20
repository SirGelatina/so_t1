#include "header.h"

Concatenator jumpconcat;

void * function_concatenator(){

	sem_init(&jumpconcat.input_pc_m, 0, 0);
	sem_init(&jumpconcat.input_shift_m, 0, 0);

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	jumpconcat.input_pc = &PC.output;
	jumpconcat.input_shift = &shift_two.output;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		printf("Init concat\n");
		fflush(0);

		// DOWN nos sem_t da entrada
		sem_wait(&jumpconcat.input_pc_m);
		sem_wait(&jumpconcat.input_shift_m);

		jumpconcat.output = (*jumpconcat.input_pc & 0xf0000000) | (*jumpconcat.input_shift & 0x0fffffff);

		// UP no sem_t de entrada da unidade que utiliza essa saida
		sem_post(&mux5.input_m[2]);

		printf("Ready concat\n");
		fflush(0);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Concatenator\n");
    fflush(0);

    pthread_exit(0);
}