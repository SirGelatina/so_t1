#include "header.h"

#define switchbit(a, b) controlbits = a ? (controlbits | b) : (controlbits & (~b))

#define STATE_instructionfetch 0
#define STATE_registerfetch 1
#define STATE_computeaddress 2
#define STATE_memoryaccess_read 3
#define STATE_memreadfinish 4
#define STATE_memoryaccess_write 5
#define STATE_execution 6
#define STATE_Rconclusion 7
#define STATE_branchconclusion 8
#define STATE_jumpconclusion 9

struct controlunit{
	int * op;

	pthread_mutex_t op_m;

	int ControlBits;
}

ControlUnit controlunit;

void state_instructionfetch(){
	int controlbits = 0;

	switchbit(1, bit_MemRead);
	switchbit(0, bit_ALUSrcA);
	switchbit(0, bit_IorD);
	switchbit(1, bit_IRWrite);
	switchbit(1, bit_ALUSrcB0);
	switchbit(0, bit_ALUSrcB1);
	switchbit(0, bit_ALUOp0);
	switchbit(0, bit_ALUOp1);
	switchbit(1, bit_PCWrite);
	switchbit(0, bit_PCSource0);
	switchbit(0, bit_PCSource1);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	return STATE_registerfetch;
}

void state_registerfetch(){
	int controlbits = 0;

	switchbit(0, bit_ALUSrcA);
	switchbit(1, bit_ALUSrcB0);
	switchbit(1, bit_ALUSrcB1);
	switchbit(0, bit_ALUOp0);
	switchbit(0, bit_ALUOp0);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	int opcode = *op;

	if(opcode == op_lw || opcode == op_sw)
		return STATE_computeaddress;
	else if(opcode == op_r_type)
		return STATE_execution;
	else if(opcode == op_beq)
		return STATE_branchconclusion;
	else if(opcode == op_jump)
		return STATE_jumpconclusion;
	else{
		// ERRO FATAL
		printf("INSTRUCAO INVALIDA.\n");

		return 0;
	}
}

void state_computeaddress(){
	int controlbits = 0;

	switchbit(1, bit_ALUSrcA);
	switchbit(0, bit_ALUSrcB0);
	switchbit(1, bit_ALUSrcB1);
	switchbit(0, bit_ALUOp0);
	switchbit(0, bit_ALUOp1);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	int opcode = *op;

	if(opcode == op_lw)
		return STATE_memoryaccess_read;
	else(opcode == op_sw)
		return STATE_memoryaccess_write;
	else{
		// ERRO FATAL
		printf("INSTRUCAO INVALIDA.\n");

		return 0;
	}
}

void state_memoryaccess_read(){
	int controlbits = 0;

	switchbit(1, bit_MemRead);
	switchbit(1, bit_IorD);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	return STATE_memreadfinish;
}

void state_memreadfinish(){
	int controlbits = 0;

	switchbit(1, bit_RegDst);
	switchbit(1, bit_RegWrite);
	switchbit(0, bit_MemtoReg);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	return STATE_instructionfetch;
}

void state_memoryaccess_write(){
	int controlbits = 0;

	switchbit(1, bit_MemWrite);
	switchbit(1, bit_IorD);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	return STATE_instructionfetch;
}

void state_execution(){
	int controlbits = 0;

	switchbit(1, bit_ALUSrcA);
	switchbit(0, bit_ALUSrcB0);
	switchbit(0, bit_ALUSrcB1);
	switchbit(1, bit_ALUOp0);
	switchbit(1, bit_ALUOp1);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	return STATE_Rconclusion;
}

void state_Rconclusion(){
	int controlbits = 0;

	switchbit(1, bit_RegDst);
	switchbit(1, bit_RegWrite);
	switchbit(0, bit_MemtoReg);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	return STATE_instructionfetch;
}

void state_branchconclusion(){
	int controlbits = 0;

	switchbit(1, bit_ALUSrcA);
	switchbit(0, bit_ALUSrcB0);
	switchbit(0, bit_ALUSrcB1);
	switchbit(1, bit_ALUOp0);
	switchbit(0, bit_ALUOp1);
	switchbit(1, bit_PCWriteCond);
	switchbit(1, bit_PCSource1);
	switchbit(0, bit_PCSource0);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	return STATE_instructionfetch;
}

void state_jumpconclusion(){
	int controlbits = 0;

	switchbit(1, bit_PCWrite);
	switchbit(0, bit_PCSource0);
	switchbit(1, bit_PCSource1);

	controlunit.ControlBits = controlbits;

	pthread_barrier_wait(&controlsync);
	pthread_mutex_lock(&controlunit.op_m);

	return STATE_instructionfetch;
}


void function_controlunit(){
	controlunit.op = &IR.output_5_0;

	pthread_barrier_wait(&clocksync);

	int * StateArray[]() = {
		state_instructionfetch,
		state_registerfetch,
		state_computeaddress,
		state_memoryaccess_read,
		state_memreadfinish,
		state_memoryaccess_write,
		state_execution,
		state_Rconclusion,
		state_branchconclusion,
		state_jumpconclusion
	}

	int CurrentState = STATE_instructionfetch;

	while(1){
		pthread_mutex_unlock(&mux6.input_m[2]);
		
		CurrentState = StateArray[CurrentState]();
		
		pthread_barrier_wait(&clocksync);
	}
}