#include "header.h" 

/*---------------- REGISTRADORES DE CONTROLE... ----------------*/
typedef struct control_register{

	int *input;
    	int output;
	mutex *control_register_m; 	

}Control_register;

// IR e PC não estão inclusos, pois são tratados separadamente (instructionregister.c e pc.c, respectivamente)
Control_register PC, MDR, A, B, ALUOut; 

void function_control_register(Control_register *r, int *output){

	// Execução da função
	while(1){

		r->output = r->input;



		pthread_barrier_wait(&clocksync)
	}
}

