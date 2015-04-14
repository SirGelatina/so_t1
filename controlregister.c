#include "header.h" 

/*---------------- REGISTRADORES DE CONTROLE... ----------------*/
typedef struct control_register{

	int *input;
    	int output;
	int n_output;
	mutex input_m;
	mutex *output_m[2]; 	

}Control_register;

// IR e PC não estão inclusos, pois são tratados separadamente (instructionregister.c e pc.c, respectivamente)
Control_register MDR, A, B, ALUOut; 

void function_control_register(Control_register *r){

	// Execução da função
	while(1){

		sem_wait(&input_m);		

		r->output = r->input;

		int i;

		for(i=0; i< r->n_output; i++){
			
			sem_post(&output_m[i]);
		}

		pthread_barrier_wait(&clocksync)
	}
}

