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

		// DOWN no pthread_mutex_t da entrada
		pthread_mutex_lock(&shiftunit->input_m);

		shiftunit->output = (*shiftunit->input) << 2;

		// UP nos pthread_mutex_t de entrada da unidade que utiliza essa saida
		pthread_mutex_unlock(shiftunit->output_m);
		
		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Shift Anonimo\n");
    fflush(0);

    pthread_exit(0);
}