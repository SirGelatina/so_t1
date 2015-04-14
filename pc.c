#include "header.h" 

/*---------------- PC ----------------*/

typedef struct pc_register{

	int *input;
	int *SC;
    int output;	

}PC_register;

void function_pc_register(){

	// Inicialização de PC
	PC.output = 0;

	PC.input = &mux5.output;

	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(1){

		if(PC.SC & separa_PCWrite != 0) // PC deve ver se vai ser atualizado
			PC.output = PC.input;

		pthread_barrier_wait(&clocksync)
	}
}

