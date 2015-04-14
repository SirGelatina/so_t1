#include "header.h" 

/*---------------- PC ----------------*/

typedef struct pc_register{

	int *input, *SC;
    int output;

	mutex input_m, SC_m;

}PC_register;

PC_register PC;

void function_pc_register(){

	// Inicialização de PC
	PC.output = 0;

	PC.input = &mux5.output;
	PC.SC = &OR_AND.output;

	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(1){

		sem_wait(&PC.input_m);
		sem_wait(&PC.SC_m);

		if(PC.SC == 1) PC.output = PC.input;

		sem_post(&mux1.input_m[0]);
		sem_post(&mux4.input_m[1]);
		sem_post(&mux5.input_m[2]);

		pthread_barrier_wait(&clocksync)
	}
}

