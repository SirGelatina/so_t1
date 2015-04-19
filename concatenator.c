#include "header.h"

Concatenator jumpconcat;

void * function_concatenator(){

	pthread_mutex_init(&jumpconcat.input_pc_m, NULL);
	pthread_mutex_init(&jumpconcat.input_shift_m, NULL);

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	jumpconcat.input_pc = &PC.output;
	jumpconcat.input_shift = &shift_two.output;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&jumpconcat.input_pc_m);
		pthread_mutex_lock(&jumpconcat.input_shift_m);

		jumpconcat.output = (*jumpconcat.input_pc & 0xf0000000) | (*jumpconcat.input_shift & 0x0fffffff);

		// UP no pthread_mutex_t de entrada da unidade que utiliza essa saida
		pthread_mutex_unlock(&mux5.input_m[2]);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Concatenator\n");
    fflush(0);

    pthread_exit(0);
}