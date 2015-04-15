#include "header.h"

typedef struct mux{

	// Input
	int **input;

	// Output
	int output;

	// Auxiliares
	int mask1, mask0;
	int input_N;

	// Semaforos
	mutex * input_m;
	mutex * output_m;

}Mux;

Mux mux1, mux2, mux3, mux4, mux5, mux6;

/*
	0x0000, separa_IorD - mux1 
	0x0000, separa_RegDst - mux2
	0x0000, separa_MemtoReg - mux3 
	0x0000, separa_ALUSrcA - mux4 
	separa_ALUSrcB1, separa_ALUSrcB0 - mux5
	separa_PCSource1, separa_PCSource0 - mux6
*/

void function_mux (Mux *mux){

	while(1){

		int i;

		for(i=0; i<(mux->input_N); i++)
			sem_wait(&mux.input_m[i]);

		int bit1, bit0;

		if(mux->mask1 & controlunit.ControlBits == 0) bit1 = 0;
		else bit1 = 1;

		if(mux->mask0 & controlunit.ControlBits == 0) bit0 = 0;
		else bit0 = 1;

		//  bit1  |   bit0  |  resultado
		//   0    |    0    |     00
		//   0    |    1    |     01
		//   1    |    0    |     10
		//   1    |    1    |     11

		if(bit1 == 0 && bit0 == 0) mux->output = mux->input[0];
		if(bit1 == 0 && bit0 == 1) mux->output = mux->input[1];
		if(bit1 == 1 && bit0 == 0) mux->output = mux->input[2];
		if(bit1 == 1 && bit0 == 1) mux->output = mux->input[3];

		sem_post(&mux->output_m);		

		pthread_barrier_wait(&clocksync);

	}

}