#include "header.h"

struct shift{

	// Input
	int * input;

	// Output
	int output;

	// pthread_mutex_t
	pthread_mutex_t input_m;
	pthread_mutex_t * output_m;
};

//Unidades funcionais que representarão os shifts
Shift shift_one;
Shift shift_two;

//Função responsável por controlar a unidade funcional
void function_shift(Shift * shiftunit){

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(1){

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&shiftunit->input_m);

		shiftunit->output = (*shiftunit->input) << 2;

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(shiftunit->output_m);
		
		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}
}