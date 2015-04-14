#include "header.h"

//Declarando a estrutura responsável pelo shift
typedef struct shift{
	int * input;

	mutex input_m;

	int output;

}Shift;

//Declarando as variáveis que representarão as unidades funcionais
Shift shift_one;
Shift shift_two;

//Função responsável por controlar a unidade funcional
void function_shift(){
	
	pthread_barrier_wait(&clocksync);

	while(1){
		z.output = (*z.input) << 2;
		
		pthread_barrier_wait(&clocksync);
	}
}