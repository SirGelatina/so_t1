#include <pthread.h>
#include <stdio.h>

#include "header.h"

pthread_barrier_t clocksync;

int main(){
	pthread_barrier_init(&clocksync, NULL, THREAD_NUMBER);

	/*------------ INICIALIZAÇÃO DAS UNIDADES GENÉRICAS ------------*/
	
	// Registradores de controle

	MDR.input = &memory.MemData;
	MDR.n_output = 1;
	MDR.output_m = (**mutex)malloc(1*(sizeof(*mutex)));
	MDR.output_m[0] = &mux3.input_m[1];

	A.input = &fileRegister.readData1;
	A.n_output = 1;
	A.output_m = (**mutex)malloc(1*(sizeof(*mutex)));
	A.output_m[0] = &mux4.input_m[1];

	B.input = &fileRegister.readData2;
	B.n_output = 2;
	B.output_m = (**mutex)malloc(2*(sizeof(*mutex)));
	B.output_m[0] = &mux6.input_m[0];
	B.output_m[1] = &memory.WriteData_m;

	ALUOut.input = &ALU.output_alu_result;
 	ALUOut.n_output = 2;
 	ALUOut.output_m = (**mutex)malloc(2*(sizeof(*mutex)));
 	ALUOut.output_m[0] = &mux1.input_m[1];
 	ALUOut.output_m[1] = &mux5.input_m[1];


	// Mux

	/*	Mascaras dos mux

	mux1 - 0x0000, separa_IorD 
	mux2 - 0x0000, separa_RegDst
	mux3 - 0x0000, separa_MemtoReg
	mux4 - 0x0000, separa_ALUSrcA
	mux5 - separa_PCSource1, separa_PCSource0 
	mux6 - separa_ALUSrcB1, separa_ALUSrcB0 	*/
	
	mux1.input = (**mutex)malloc(2*(sizeof(*mutex)));
	mux1.input[0] = &PC.output;
	mux1.input[1] = &ALUOut.output;
	mux1.mask1 = 0x0000;
	mux1.mask0 = separa_IorD;
	mux1.input_N = 2;
	mux1.output_m = &memory.Address_m;

	mux2.input = (**mutex)malloc(2*(sizeof(*mutex)));
	mux2.input[0] = &IR.output_20_16;
	mux2.input[1] = &IR.output_15_11;
	mux2.mask1 = 0x0000;
	mux2.mask0 = separa_RegDst;
	mux2.input_N = 2;
	mux2.output_m = &fileRegister.write_reg_m;

	mux3.input = (**mutex)malloc(2*(sizeof(*mutex)));
	mux3.input[0] = &ALUOut.output;
	mux3.input[1] = &MDR.output;
	mux3.mask1 = 0x0000;
	mux3.mask0 = separa_MemtoReg;
	mux3.input_N = 2;
	mux3.output_m = &fileRegister.write_data_m;

	mux4.input = (**mutex)malloc(2*(sizeof(*mutex)));
	mux4.input[0] = &PC.output;
	mux4.input[1] = &A.output;
	mux4.mask1 = 0x0000;
	mux4.mask0 = separa_ALUSrcA;
	mux4.input_N = 2;
	mux4.output_m = &ALU.input_mux_one_m;

	mux5.input = (**mutex)malloc(3*(sizeof(*mutex)));
	mux5.input[0] = &ALU.output_alu_result;
	mux5.input[1] = &ALUOut.output;
	mux5.input[2] = &shift_two.output;
	mux5.mask1 = separa_PCSource1;
	mux5.mask0 = separa_PCSource0;
	mux5.input_N = 3;
	mux5.output_m = &PC.input_m;

	mux6.input = (**mutex)malloc(4*(sizeof(*mutex)));
	mux6.input[0] = &B.output;
	mux6.input[1] = 4;
	mux6.input[2] = &extend.output;
	mux6.input[3] = &shift_one.output;
	mux6.mask1 = separa_ALUSrcB1;
	mux6.mask0 = separa_ALUSrcB0;
	mux6.input_N = 4;
	mux6.output_m = &ALU.input_mux_two_m;
	
}
