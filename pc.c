#include "header.h" 

Pc_register PC;

void * function_pc_register(){
	sem_init(&PC.input_m, 0, 0);
	sem_init(&PC.SC_m, 0, 0);

	// Inicialização de PC
	PC.output = 0;

	// Ligacao das entradas dessa unidade funcional com as saidas de onde virao os dados
	PC.input = &mux5.output;
	PC.SC = &OR_AND.output;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// UP nos sem_t de entrada das unidades que utilizam essas saidas
		sem_post(&mux1.input_m[0]);
		sem_post(&mux4.input_m[0]);
		sem_post(&jumpconcat.input_pc_m);

		// DOWN nos sem_t da entrada
		sem_wait(&PC.input_m);
		sem_wait(&PC.SC_m);

		PC.buffer = *PC.input;

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);

		if(*PC.SC == 1) PC.output = PC.buffer;
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Registrador PC\n");
    fflush(0);

    pthread_exit(0);
}

