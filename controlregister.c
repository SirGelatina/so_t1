#include "header.h" 

struct control_register{

	// Input
	int *input;

	// Output
    int output;

    // Auxiliares
	int n_output; // Número de saídas

	// pthread_mutex_t	
	pthread_mutex_t input_m;
	pthread_mutex_t ** output_m; 	

};

// IR e PC não estão inclusos, pois são tratados separadamente (instructionregister.c e pc.c, respectivamente)
Control_register MDR, A, B, ALUOut; 

void function_control_register(Control_register *r){

	// Execução da função
	while(isRunning){

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
}