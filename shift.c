#include "header.h"

//Declarando a estrutura responsável pelo shift
struct shift{
	int * input;

	mutex input_m;

	int output;

	mutex * output_m;
};

//Declarando as variáveis que representarão as unidades funcionais
Shift shift_one;
Shift shift_two;

//Função responsável por controlar a unidade funcional
void function_shift(Shift * shiftunit){
	int i;
	
	pthread_barrier_wait(&clocksync);

	while(1){
		sem_wait(&shiftunit->input_m);

		shiftunit->output = (*shiftunit->input) << 2;

		sem_post(shiftunit->output_m);
		
		pthread_barrier_wait(&clocksync);
	}
}