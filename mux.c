#include "header.h"

typedef struct mux{

	// Input
	int *input_0, *input_1, *input_2, *input_3;
	int *SC;

	// Output
	int output;

}Mux;

Mux mux1, mux2, mux3, mux4, mux5, mux6;

mux1->input_0 = ;
mux1->input_1 = ;
mux1->input_2 = NULL;
mux1->input_3 = NULL;
mux1->SC = ;

mux2->input_0 = ;
mux2->input_1 = ;
mux2->input_2 = NULL;
mux2->input_3 = NULL;
mux2->SC = ;

mux3->input_0 = ;
mux3->input_1 = ;
mux3->input_2 = NULL;
mux3->input_3 = NULL;
mux3->SC = ;

mux4->input_0 = ;
mux4->input_1 = ;
mux4->input_2 = NULL;
mux4->input_3 = NULL;
mux4->SC = ;

mux5->input_0 = ;
mux5->input_1 = ;
mux5->input_2 = ;
mux5->input_3 = NULL;
mux5->SC = ;

mux6->input_0 = ;
mux6->input_1 = ;
mux6->input_2 = ;
mux6->input_3 = ;
mux6->SC = ;

/*
Functions parameters: 
	0x0000, separa_IorD, mux1 
	0x0000, separa_RegDst, mux2
	0x0000, separa_MemtoReg, mux3 
	0x0000, separa_ALUSrcA, mux4 
	separa_ALUSrcB1, separa_ALUSrcB0, mux5
	separa_PCSource1, separa_PCSource0, mux6

*/

void function_mux (int mask1, int mask0, Mux *mux){

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

}