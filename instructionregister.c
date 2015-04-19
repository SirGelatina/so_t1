#include "header.h"

Instruction_register IR;

void * function_instruction_register(){
	pthread_mutex_init(&IR.input_instruction_m, NULL);

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	IR.input_instruction = &memory.MemData;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&IR.input_instruction_m);

		// Espera pela unidade de controle
		pthread_mutex_lock(&controlmutex);
		while(!controlready) // p2
			pthread_cond_wait(&controlsync, &controlmutex);
		pthread_mutex_unlock(&controlmutex);

		// If IRWrite == 1
		if((controlunit.ControlBits & bit_IRWrite) != 0){
			IR.output_31_26 = ((*IR.input_instruction) >> 26);
			IR.output_25_21 = ((*IR.input_instruction & bit_rs) >> 21);
			IR.output_25_0  = (*IR.input_instruction & bit_endereco_jump);
			IR.output_20_16 = ((*IR.input_instruction & bit_rt) >> 16);
			IR.output_15_0  = (*IR.input_instruction & bit_imediato);
			IR.output_15_11 = ((*IR.input_instruction & bit_rd) >> 11);
			IR.output_5_0   = (*IR.input_instruction & bit_cfuncao);
		}

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(&controlunit.op_m);
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

	if(EXITMESSAGE)
		printf("FINALIZADO: Registrador de Instrucoes\n");
    fflush(0);

    pthread_exit(0);
}