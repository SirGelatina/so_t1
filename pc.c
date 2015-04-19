#include "header.h" 

Pc_register PC;

void * function_pc_register(){
	pthread_mutex_init(&PC.input_m, NULL);
	pthread_mutex_init(&PC.SC_m, NULL);

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

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&PC.input_m);
		pthread_mutex_lock(&PC.SC_m);

		if(*PC.SC == 1) PC.output = *PC.input;

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(&mux1.input_m[0]);
		pthread_mutex_unlock(&mux4.input_m[1]);
		pthread_mutex_unlock(&jumpconcat.input_pc_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Registrador PC\n");
    fflush(0);

    pthread_exit(0);
}

