#include "header.h" 

/*---------------- PC ----------------*/

typedef struct pc_register{

	int *input;
	int *SC;
        int output;
	mutex input_m;
	mutex output_m;	

}PC_register;

PC_register PC;

void function_pc_register(){

	// Inicialização de PC
	PC.output = 0;

	PC.input = &mux5.output;

	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(1){

		sem_wait(&input_m);

		if(PC.SC & separa_PCWrite != 0) // PC deve ver se vai ser atualizado
			PC.output = PC.input;

		sem_post(&output_m);

		pthread_barrier_wait(&clocksync)
	}
}

