#include <pthread.h>
#include <stdio.h>

#include "header.h"

pthread_barrier_t clocksync;

int main(){
	pthread_barrier_init(&clocksync, NULL, THREAD_NUMBER);

	/*------------ INICIALIZAÇÃO DAS UNIDADES GENÉRICAS ------------*/
	
	// Registradores de controle
	r->output = ;
	r->input = &output;

/*
	0x0000, separa_IorD - mux1 
	0x0000, separa_RegDst - mux2
	0x0000, separa_MemtoReg - mux3 
	0x0000, separa_ALUSrcA - mux4 
	separa_ALUSrcB1, separa_ALUSrcB0 - mux5
	separa_PCSource1, separa_PCSource0 - mux6
*/

	// Mux
	mux1.input[0] = &PC.output;
	mux1.input[1] = &ALUOut.output;
	mux1.mask1 = 0x0000;
	mux1.mask0 = separa_IorD;

	mux2.input[0] = &IR.output_20_16;
	mux2.input[1] = &IR.output_15_11;
	mux2.mask1 = 0x0000;
	mux2.mask0 = separa_RegDst;

	mux3.input[0] = &ALUOut.output;
	mux3.input[1] = &MDR.output;
	mux3.mask1 = 0x0000;
	mux3.mask0 = separa_MemtoReg;

	mux4.input[0] = &PC.output;
	mux4.input[1] = &A.output;
	mux4.mask1 = 0x0000;
	mux4.mask0 = separa_ALUSrcA;

	mux5.input[0] = &ALU.output_alu_result;
	mux5.input[1] = &ALUOut.output;
	mux5.input[2] = &shift_two.output;
	mux5.mask1 = separa_PCSource1;
	mux5.mask0 = separa_PCSource0;

	mux6.input[0] = &B.output;
	mux6.input[1] = 4;
	mux6.input[2] = &;
	mux6.input[3] = &shift_one.output;
	mux6.mask1 = separa_ALUSrcB1;
	mux6.mask0 = separa_ALUSrcB0;

	
}
