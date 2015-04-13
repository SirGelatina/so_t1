#include "header.h"

typedef struct mux{

	// Input
	int **input;
	int *SC;

	// Output
	int output;

}Mux;

/*
Functions parameters: 
	0x0000, separa_IorD, mux1 
	0x0000, separa_RegDst, mux2
	0x0000, separa_MemtoReg, mux3 
	0x0000, separa_ALUSrcA, mux4 
	separa_ALUSrcB1, separa_ALUSrcB0, mux5
	separa_PCSource1, separa_PCSource0, mux6

*/

void function_mux (int mask1, int mask0, Mux *mux, int *output[]){

	mux->input[0] = &output[0];
	mux->input[1] = &output[1];
	mux->input[2] = &output[2];
	mux->input[3] = &output[3];
	mux->SC = ;

	pthread_barrier_wait(&clocksync);

	while(1){

		int bit1, bit0;

		if(mask1 & mux->SC == 0) bit1 = 0;
		else bit1 = 1;

		if(mask0 & mux->SC == 0) bit0 = 0;
		else bit0 = 1;

		//  bit1  |   bit0  |  resultado
		//   0    |    0    |     00
		//   0    |    1    |     01
		//   1    |    0    |     10
		//   1    |    1    |     11

		if(bit1 == 0 && bit0 == 0) mux->output = mux->input_0;
		if(bit1 == 0 && bit0 == 1) mux->output = mux->input_1;
		if(bit1 == 1 && bit0 == 0) mux->output = mux->input_2;
		if(bit1 == 1 && bit0 == 1) mux->output = mux->input_3;

		pthread_barrier_wait(&clocksync);

	}

}