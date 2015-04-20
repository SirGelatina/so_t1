#include "header.h"

Or_and OR_AND;

void * function_or_and(){
	sem_init(&OR_AND.zero_m, 0, 0);

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	OR_AND.zero = &ALU.output_alu_zero;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN nos sem_t da entrada
		sem_wait(&OR_AND.zero_m);

		// Espera pela unidade de controle
		pthread_mutex_lock(&controlmutex);
		while(!controlready) // p2
			pthread_cond_wait(&controlsync, &controlmutex);
		pthread_mutex_unlock(&controlmutex);

		int PCWriteCond = controlunit.ControlBits & bit_PCWriteCond;
		int PCWrite = controlunit.ControlBits & bit_PCWrite;

		OR_AND.output = (*OR_AND.zero && PCWriteCond) || PCWrite;

		// UP nos sem_t de entrada das unidades que utilizam essas saidas
		sem_post(&PC.SC_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);

	}

	if(EXITMESSAGE)
		printf("FINALIZADO: or/and\n");
    fflush(0);

    pthread_exit(0);
}
