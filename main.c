#include <pthread.h>
#include <stdio.h>

#include "header.h"

pthread_barrier_t clocksync;
pthread_barrier_t controlsync;

int isRunning;

int main(){
	int i;
	isRunning = 1;

	pthread_barrier_init(&clocksync, NULL, THREAD_NUMBER);

	/*------------ INICIALIZAÇÃO DAS UNIDADES GENÉRICAS ------------*/
	
	// Registradores de controle

	MDR.input = &memory.MemData;
	MDR.n_output = 1;
	MDR.output_m = (**pthread_mutex_t)malloc(1*(sizeof(*pthread_mutex_t)));
	MDR.output_m[0] = &mux3.input_m[1];

	pthread_mutex_init(&MDR.input_m, NULL);

	A.input = &fileRegister.readData1;
	A.n_output = 1;
	A.output_m = (**pthread_mutex_t)malloc(1*(sizeof(*pthread_mutex_t)));
	A.output_m[0] = &mux4.input_m[1];

	pthread_mutex_init(&A.input_m, NULL);

	B.input = &fileRegister.readData2;
	B.n_output = 2;
	B.output_m = (**pthread_mutex_t)malloc(2*(sizeof(*pthread_mutex_t)));
	B.output_m[0] = &mux6.input_m[0];
	B.output_m[1] = &memory.WriteData_m;

	pthread_mutex_init(&B.input_m, NULL);

	ALUOut.input = &ALU.output_alu_result;
 	ALUOut.n_output = 2;
 	ALUOut.output_m = (**pthread_mutex_t)malloc(2*(sizeof(*pthread_mutex_t)));
 	ALUOut.output_m[0] = &mux1.input_m[1];
 	ALUOut.output_m[1] = &mux5.input_m[1];

	pthread_mutex_init(&ALUOut.input_m, NULL);


	// Mux

	/*	Mascaras dos mux

	mux1 - 0x0000, bit_IorD 
	mux2 - 0x0000, bit_RegDst
	mux3 - 0x0000, bit_MemtoReg
	mux4 - 0x0000, bit_ALUSrcA
	mux5 - bit_PCSource1, bit_PCSource0 
	mux6 - bit_ALUSrcB1, bit_ALUSrcB0 	*/

		/*	Inicializacao do Mux 1 	*/
	
	mux1.input = (**int)malloc(2*(sizeof(*int)));
	mux1.input[0] = &PC.output;
	mux1.input[1] = &ALUOut.output;
	mux1.mask1 = 0x0000;
	mux1.mask0 = bit_IorD;
	mux1.input_N = 2;
	mux1.output_m = &memory.Address_m;

	mux1.input_m = (*pthread_mutex_t)malloc(2*sizeof(pthread_mutex_t));
	for(i=0; i<2; i++)
		pthread_mutex_init(&mux1.input_m[i], NULL);

		/*	Inicializacao do Mux 2 	*/

	mux2.input = (**int)malloc(2*(sizeof(*int)));
	mux2.input[0] = &IR.output_20_16;
	mux2.input[1] = &IR.output_15_11;
	mux2.mask1 = 0x0000;
	mux2.mask0 = bit_RegDst;
	mux2.input_N = 2;
	mux2.output_m = &fileRegister.write_reg_m;
	
	mux2.input_m = (*pthread_mutex_t)malloc(2*sizeof(pthread_mutex_t));
	for(i=0; i<2; i++)
		pthread_mutex_init(&mux2.input_m[i], NULL);

		/*	Inicializacao do Mux 3	*/

	mux3.input = (**int)malloc(2*(sizeof(*int)));
	mux3.input[0] = &ALUOut.output;
	mux3.input[1] = &MDR.output;
	mux3.mask1 = 0x0000;
	mux3.mask0 = bit_MemtoReg;
	mux3.input_N = 2;
	mux3.output_m = &fileRegister.write_data_m;
	
	mux3.input_m = (*pthread_mutex_t)malloc(2*sizeof(pthread_mutex_t));
	for(i=0; i<2; i++)
		pthread_mutex_init(&mux3.input_m[i], NULL);

		/*	Inicializacao do Mux 4 	*/

	mux4.input = (**int)malloc(2*(sizeof(*int)));
	mux4.input[0] = &PC.output;
	mux4.input[1] = &A.output;
	mux4.mask1 = 0x0000;
	mux4.mask0 = bit_ALUSrcA;
	mux4.input_N = 2;
	mux4.output_m = &ALU.input_mux_one_m;
	
	mux4.input_m = (*pthread_mutex_t)malloc(2*sizeof(pthread_mutex_t));
	for(i=0; i<2; i++)
		pthread_mutex_init(&mux4.input_m[i], NULL);

		/*	Inicializacao do Mux 5 	*/

	mux5.input = (**int)malloc(3*(sizeof(*int)));
	mux5.input[0] = &ALU.output_alu_result;
	mux5.input[1] = &ALUOut.output;
	mux5.input[2] = &shift_two.output;
	mux5.mask1 = bit_PCSource1;
	mux5.mask0 = bit_PCSource0;
	mux5.input_N = 3;
	mux5.output_m = &PC.input_m;
	
	mux5.input_m = (*pthread_mutex_t)malloc(3*sizeof(pthread_mutex_t));
	for(i=0; i<2; i++)
		pthread_mutex_init(&mux5.input_m[i], NULL);

		/*	Inicializacao do Mux 6 	*/

	int fourconstant = 4;

	mux6.input = (**int)malloc(4*(sizeof(*int)));
	mux6.input[0] = &B.output;
	mux6.input[1] = &fourconstant;
	mux6.input[2] = &extend.output;
	mux6.input[3] = &shift_one.output;
	mux6.mask1 = bit_ALUSrcB1;
	mux6.mask0 = bit_ALUSrcB0;
	mux6.input_N = 4;
	mux6.output_m = &ALU.input_mux_two_m;
	
	mux6.input_m = (*pthread_mutex_t)malloc(4*sizeof(pthread_mutex_t));
	for(i=0; i<2; i++)
		pthread_mutex_init(&mux6.input_m[i], NULL);

		/*	Inicializacao do Shift Left 2 #1 	*/

	shift_one.input = &extend.output;
	shift_one.output_m = &mux6.input_m[3];

	pthread_mutex_init(&shift_one.input_m, NULL);

		/*	Inicializacao do Shift Left 2 #2 	*/

	shift_two.input = &IR.output_25_0;
	shift_two.output_m = &jumpconcat.input_shift_m;

	pthread_mutex_init(&shift_two.input_m, NULL);

		/*
			Criando as threads
								*/

	pthread_t threadArray = (pthread *)malloc(10*sizeof(pthread_t));
	int size = 0;

		// Unidades funcionais unicas

	pthread_create(threadArray + size++, NULL, function_memory, NULL);
	pthread_create(threadArray + size++, NULL, function_instruction_register, NULL);
	pthread_create(threadArray + size++, NULL, function_or_and, NULL);
	pthread_create(threadArray + size++, NULL, function_fileregister, NULL);
	pthread_create(threadArray + size++, NULL, function_alu, NULL);
	pthread_create(threadArray + size++, NULL, function_alucontrol, NULL);
	pthread_create(threadArray + size++, NULL, function_pc_register, NULL);
	pthread_create(threadArray + size++, NULL, function_controlunit, NULL);
	pthread_create(threadArray + size++, NULL, function_signalextend, NULL);
	pthread_create(threadArray + size++, NULL, function_concatenator, NULL);

		// Unidades funcionais genericas

	pthread_create(threadArray + size++, NULL, function_mux, (void *) &mux1);
	pthread_create(threadArray + size++, NULL, function_mux, (void *) &mux2);
	pthread_create(threadArray + size++, NULL, function_mux, (void *) &mux3);
	pthread_create(threadArray + size++, NULL, function_mux, (void *) &mux4);
	pthread_create(threadArray + size++, NULL, function_mux, (void *) &mux5);
	pthread_create(threadArray + size++, NULL, function_mux, (void *) &mux6);

	pthread_create(threadArray + size++, NULL, function_shift, (void *) &shift_one);
	pthread_create(threadArray + size++, NULL, function_shift, (void *) &shift_two);

	pthread_create(threadArray + size++, NULL, function_control_register, (void *) &ALUOut);
	pthread_create(threadArray + size++, NULL, function_control_register, (void *) &MDR);
	pthread_create(threadArray + size++, NULL, function_control_register, (void *) &A);
	pthread_create(threadArray + size++, NULL, function_control_register, (void *) &B);

		/*
			Aguardando o fim da execucao das threads
														*/

	for(i=0; i<size; i++)
		threadArray(threadArray[i], NULL);

		/*
			Imprimindo o resultado da memoria e registradores
																*/



	return 0;
}
