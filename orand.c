#include "header.h"

typedef struct or_and{

	// Input
	int *zero;
	int *PCWriteCond, *PCWrite;

	// Output
	int output;

	// Mutex
	mutex zero_m;

}Or_and;

Or_and OR_AND;

void function_or_and(){

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	OR_AND.zero = &ALU.output_alu_zero;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(1){

		// DOWN nos mutex da entrada
		sem_wait(&OR_AND.zero_m);

		if (controlunit.ControlBits & separa_PCWriteCond == 0) OR_AND.PCWriteCond = 0;
		else OR_AND.PCWriteCond = 1;

		if (controlunit.ControlBits & separa_PCWrite == 0) OR_AND.PCWrite = 0;
		else OR_AND.PCWrite = 1;

		OR_AND.output = (OR_AND.zero & OR_AND.PCWriteCond) | OR_AND.PCWrite;

		// UP nos mutex de entrada das unidades que utilizam essas saidas
		sem_post(&PC.SC_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);

	}

}

