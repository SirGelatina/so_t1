#include "header.h" 

// IR e PC não estão inclusos, pois são tratados separadamente (instructionregister.c e pc.c, respectivamente)
Control_register MDR, A, B, ALUOut; 

void * function_control_register(void * arg){
	Control_register * r = (Control_register *)arg;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN no pthread_mutex_t da entrada
		pthread_mutex_lock(&r->input_m);		

		r->output = *r->input;

		// UP no pthread_mutex_t de entrada das unidades que utiliza essa saida
		int i;
		for(i = 0; i < r->n_output; i++)
			pthread_mutex_unlock(r->output_m[i]);
		
		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Control Register Anonimo\n");
    fflush(0);

    pthread_exit(0);
}