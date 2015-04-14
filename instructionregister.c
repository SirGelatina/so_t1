#include "header.h"

typedef struct instruction_register{

	// Input
	int *input_instruction, *input_SC;

	// Output
	int output_31_26, output_25_21, output_25_0, output_20_16, output_15_0, output_15_11, output_5_0;

	// Semaforo
	mutex input_instruction_m;

}Instruction_register;

Instruction_register IR;

void function_instruction_register(){

	IR.input_instruction = &memory.MemData;
	IR.input_SC = &;

	pthread_barrier_wait(&clocksync);

	while(1){

		sem_wait(&IR.input_instruction);

		// If IRWrite == 1
		if(IR.input_SC & separa_IRWrite != 0){
			IR.output_31_26 = (IR.input_instruction) >> 26;
			IR.output_25_21 = (IR.input_instruction & separa_rs) >> 21;
			IR.output_25_0  = (IR.input_instruction & separa_endereco_jump);
			IR.output_20_16 = (IR.input_instruction & separa_rt) >> 16;
			IR.output_15_0  = (IR.input_instruction & separa_imediato;
			IR.output_15_11 = (IR.input_instruction & separa_rd) >> 11;
			IR.output_5_0   = (IR.input_instruction & separa_cfuncao);
		}

		sem_post(&...);
		.
		.
		.

		pthread_barrier_wait(&clocksync);	

	}
}