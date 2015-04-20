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

		// UP no sem_t de entrada das unidades que utiliza essa saida
		int i;
		for(i = 0; i < r->n_output; i++){
			sem_post(r->output_m[i]);
		}

		printf("Init register %s\n", r->name);
		fflush(0);

		// DOWN no sem_t da entrada
		sem_wait(&r->input_m);
		r->buffer = *r->input;

		printf("Ready register %s\n", r->name);
		fflush(0);
		
		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);

		// O conteudo escrito neste ciclo so pode ser lido no proximo!
		r->output = r->buffer;
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Control Register Anonimo\n");
    fflush(0);

    pthread_exit(0);
}