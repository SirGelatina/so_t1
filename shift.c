#include "header.h"

//Unidades funcionais que representarão os shifts
Shift shift_one;
Shift shift_two;

//Função responsável por controlar a unidade funcional
void * function_shift(void * arg){
	Shift * shiftunit = (Shift *)arg;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN no sem_t da entrada
		sem_wait(&shiftunit->input_m);

		shiftunit->output = (*shiftunit->input) << 2;

		// UP nos sem_t de entrada da unidade que utiliza essa saida
		sem_post(shiftunit->output_m);
		
		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Shift Anonimo\n");
    fflush(0);

    pthread_exit(0);
}