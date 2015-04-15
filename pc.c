#include "header.h" 

typedef struct pc_register{

	// Input 
	int *input, *SC;

	// Output
    int output;

    // pthread_mutex_t
	pthread_mutex_t input_m, SC_m;

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

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&PC.input_m);
		pthread_mutex_lock(&PC.SC_m);

		if(PC.SC == 1) PC.output = PC.input;

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(&mux1.input_m[0]);
		pthread_mutex_unlock(&mux4.input_m[1]);
		pthread_mutex_unlock(&jumpconcat.input_pc_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}
}

