#include "header.h"

struct or_and{

	// Input
	int *zero;
	int *PCWriteCond, *PCWrite;

	// Output
	int output;

	// pthread_mutex_t
	pthread_mutex_t zero_m;

};

Or_and OR_AND;

void * function_or_and(void *){

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	OR_AND.zero = &ALU.output_alu_zero;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&OR_AND.zero_m);

		if (controlunit.ControlBits & separa_PCWriteCond == 0) OR_AND.PCWriteCond = 0;
		else OR_AND.PCWriteCond = 1;

		if (controlunit.ControlBits & separa_PCWrite == 0) OR_AND.PCWrite = 0;
		else OR_AND.PCWrite = 1;

		OR_AND.output = (OR_AND.zero & OR_AND.PCWriteCond) | OR_AND.PCWrite;

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(&PC.SC_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);

	}
}