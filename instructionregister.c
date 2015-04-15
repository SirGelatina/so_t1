#include "header.h"

typedef struct instruction_register{

	// Input
	int *input_instruction;

	// Output
	int output_31_26, output_25_21, output_25_0, output_20_16, output_15_0, output_15_11, output_5_0;

	// Mutex
	mutex input_instruction_m;

}Instruction_register;

Instruction_register IR;

void function_instruction_register(){

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	IR.input_instruction = &memory.MemData;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(1){

		// DOWN nos mutex da entrada
		sem_wait(&IR.input_instruction_m);

		// If IRWrite == 1
		if(controlunit.ControlBits & separa_IRWrite != 0){
			IR.output_31_26 = (IR.input_instruction) >> 26;
			IR.output_25_21 = (IR.input_instruction & separa_rs) >> 21;
			IR.output_25_0  = (IR.input_instruction & separa_endereco_jump);
			IR.output_20_16 = (IR.input_instruction & separa_rt) >> 16;
			IR.output_15_0  = (IR.input_instruction & separa_imediato;
			IR.output_15_11 = (IR.input_instruction & separa_rd) >> 11;
			IR.output_5_0   = (IR.input_instruction & separa_cfuncao);
		}

		// UP nos mutex de entrada das unidades que utilizam essas saidas
		sem_post(&controlunit.output_5_0_m);
		sem_post(&shift_two.input_m);
		sem_post(&fileRegister.read_reg1_m);
		sem_post(&fileRegister.read_reg2_m);
		sem_post(&mux2.input_m[0]);
		sem_post(&mux2.input_m[1]);
		sem_post(&extend.input_m);
		sem_post(&ALUControl.input_instruction_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);	

	}
}