#include "header.h"

typedef struct instruction_register{

	// Input
	int *input_instruction, *input_SC;

	// Output
	int output_31_26, output_25_21, output_25_0, output_20_16, output_15_0, output_15_11, output_5_0;

}Instruction_register;

Instruction_register ir;

void function_instruction_register(){

	ir->input_instruction = ;
	ir->input_SC = ;

	pthread_barrier_wait(&clocksync);

	while(1){

		// If IRWrite == 1
		if(ir->input_SC & separa_IRWrite != 0){
			ir.output_31_26 = (*ir->input_instruction) >> 26;
			ir.output_25_21 = (*ir->input_instruction & separa_rs) >> 21;
			ir.output_25_0  = (*ir->input_instruction & separa_endereco_jump);
			ir.output_20_16 = (*ir->input_instruction & separa_rt) >> 16;
			ir.output_15_0  = (*ir->input_instruction & separa_imediato;
			ir.output_15_11 = (*ir->input_instruction & separa_rd) >> 11;
			ir.output_5_0   = (*ir->input_instruction & separa_cfuncao);
		}

		pthread_barrier_wait(&clocksync);	

	}
}