#include "header.h" 

/*---------------- REGISTRADORES DE CONTROLE... ----------------*/
typedef struct control_register{

	int *input;
    int output;	

}Control_register;

void function_control_register(Control_register *r, int *output){

	// Inicialização dos registradores
	r->output = NULL;

	r->input = &output;
	
	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(1){

		r->output = r->input;

		pthread_barrier_wait(&clocksync)
	}
}

