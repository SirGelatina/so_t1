#include "header.h" 

typedef struct pc_register{

	// Input 
	int *input, *SC;

	// Output
    int output;

    // Mutex
	mutex input_m, SC_m;

}PC_register;

PC_register PC;

void function_pc_register(){

	// Inicialização de PC
	PC.output = 0;

	// Ligacao das entradas dessa unidade funcional com as saidas de onde virao os dados
	PC.input = &mux5.output;
	PC.SC = &OR_AND.output;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(1){

		// DOWN nos mutex da entrada
		sem_wait(&PC.input_m);
		sem_wait(&PC.SC_m);

		if(PC.SC == 1) PC.output = PC.input;

		// UP nos mutex de entrada das unidades que utilizam essas saidas
		sem_post(&mux1.input_m[0]);
		sem_post(&mux4.input_m[1]);
		sem_post(&mux5.input_m[2]);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}
}

