#include "header.h" 

/*---------------- REGISTRADORES DE CONTROLE... ----------------*/
typedef struct control_register{

	int *input;
	int *SC;
    int output;	

}Control_register;

void function_control_register(Control_register *r, int *output, int pcflag){

	r->input = &output;

	// Inicialização dos registradores

	// PC
	if(pcflag == 1) r->output = 0;
	// Outros registradores
	else r->output = NULL
	
	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(1){

		if(pcflag == 1){ // O registrador eh PC
			if(r->SC & separa_PCWrite != 0) // PC deve ver se vai ser atualizado
				x->output = x->input;
		}
		else x->output = x->input;
	}
	pthread_barrier_wait(&clocksync)
}

