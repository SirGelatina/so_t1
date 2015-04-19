#include "header.h"

Or_and OR_AND;

extern pthread_cond_t controlsync;
extern pthread_mutex_t controlmutex;
extern int controlready;

void * function_or_and(){
	pthread_mutex_init(&OR_AND.zero_m, NULL);

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	OR_AND.zero = &ALU.output_alu_zero;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&OR_AND.zero_m);

		// Espera pela unidade de controle
		pthread_mutex_lock(&controlmutex);
		while(!controlready) // p2
			pthread_cond_wait(&controlsync, &controlmutex);
		pthread_mutex_unlock(&controlmutex);

		if (controlunit.ControlBits & bit_PCWriteCond)
			*OR_AND.PCWriteCond = 1;
		else 
			*OR_AND.PCWriteCond = 0;

		if (controlunit.ControlBits & bit_PCWrite)
			*OR_AND.PCWrite = 1;
		else 
			*OR_AND.PCWrite = 0;

		OR_AND.output = (*OR_AND.zero & *OR_AND.PCWriteCond) | *OR_AND.PCWrite;

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(&PC.SC_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);

	}

	if(EXITMESSAGE)
		printf("FINALIZADO: or/and\n");
    fflush(0);

    pthread_exit(0);
}
