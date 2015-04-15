#include "header.h"

//Declarando a estrutura responsável pelo shift
struct shift{
	int * input;

	pthread_mutex_t input_m;

	int output;

	pthread_mutex_t * output_m;
};

//Declarando as variáveis que representarão as unidades funcionais
Shift shift_one;
Shift shift_two;

//Função responsável por controlar a unidade funcional
void function_shift(Shift * shiftunit){

	pthread_barrier_wait(&clocksync);

	while(1){
		pthread_mutex_lock(&shiftunit->input_m);

		shiftunit->output = (*shiftunit->input) << 2;

		pthread_mutex_unlock(shiftunit->output_m);
		
		pthread_barrier_wait(&clocksync);
	}
}