#include "header.h"

struct instruction_register{

	// Input
	int *input_instruction;

	// Output
	int output_31_26, output_25_21, output_25_0, output_20_16, output_15_0, output_15_11, output_5_0;

	// pthread_mutex_t
	pthread_mutex_t input_instruction_m;

};

Instruction_register IR;

void * function_instruction_register(void *){

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	IR.input_instruction = &memory.MemData;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&IR.input_instruction_m);

		// If IRWrite == 1
		if(controlunit.ControlBits & bit_IRWrite != 0){
			IR.output_31_26 = ((*IR.input_instruction) >> 26);
			IR.output_25_21 = ((*IR.input_instruction & bit_rs) >> 21);
			IR.output_25_0  = (*IR.input_instruction & bit_endereco_jump);
			IR.output_20_16 = ((*IR.input_instruction & bit_rt) >> 16);
			IR.output_15_0  = (*IR.input_instruction & bit_imediato);
			IR.output_15_11 = ((*IR.input_instruction & bit_rd) >> 11);
			IR.output_5_0   = (*IR.input_instruction & bit_cfuncao);
		}

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(&controlunit.output_5_0_m);
		pthread_mutex_unlock(&shift_two.input_m);
		pthread_mutex_unlock(&fileRegister.read_reg1_m);
		pthread_mutex_unlock(&fileRegister.read_reg2_m);
		pthread_mutex_unlock(&mux2.input_m[0]);
		pthread_mutex_unlock(&mux2.input_m[1]);
		pthread_mutex_unlock(&extend.input_m);
		pthread_mutex_unlock(&ALUControl.input_instruction_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);	

	}
}