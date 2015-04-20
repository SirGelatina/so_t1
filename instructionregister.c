#include "header.h"

Instruction_register IR;

void * function_instruction_register(){
	sem_init(&IR.input_instruction_m, 0, 0);

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	IR.input_instruction = &memory.MemData;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// UP nos sem_t de entrada das unidades que utilizam essas saidas
		sem_post(&controlunit.op_m);
		sem_post(&shift_two.input_m);
		sem_post(&fileRegister.read_reg1_m);
		sem_post(&fileRegister.read_reg2_m);
		sem_post(&mux2.input_m[0]);
		sem_post(&mux2.input_m[1]);
		sem_post(&extend.input_m);
		sem_post(&ALUControl.input_instruction_m);

		// DOWN nos sem_t da entrada
		sem_wait(&IR.input_instruction_m);

		// Espera pela unidade de controle
		pthread_mutex_lock(&controlmutex);
		while(!controlready) // p2
			pthread_cond_wait(&controlsync, &controlmutex);
		pthread_mutex_unlock(&controlmutex);

		IR.buffer = *IR.input_instruction;

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);	

		// If IRWrite == 1
		if(controlunit.ControlBits & bit_IRWrite){
			IR.output_31_26 = ((IR.buffer) >> 26);
			IR.output_25_21 = ((IR.buffer & bit_rs) >> 21);
			IR.output_25_0  = (IR.buffer & bit_endereco_jump);
			IR.output_20_16 = ((IR.buffer & bit_rt) >> 16);
			IR.output_15_0  = (IR.buffer & bit_imediato);
			IR.output_15_11 = ((IR.buffer & bit_rd) >> 11);
			IR.output_5_0   = (IR.buffer & bit_cfuncao);
		}

	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Registrador de Instrucoes\n");
    fflush(0);

    pthread_exit(0);
}