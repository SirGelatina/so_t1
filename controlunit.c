#include "header.h"

// Switchbit e uma funcao macro que ativa (a = 1) ou desativa (a = 0)
// os bits 1 da mascara b na variavel var

#define switchbit(var, a, b) var = a ? (var | b) : (var & (~b))

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

ControlUnit controlunit;

int state_instructionfetch(){
	int controlbits = 0;

	switchbit(controlbits, 1, bit_MemRead);
	switchbit(controlbits, 0, bit_ALUSrcA);
	switchbit(controlbits, 0, bit_IorD);
	switchbit(controlbits, 1, bit_IRWrite);
	switchbit(controlbits, 1, bit_ALUSrcB0);
	switchbit(controlbits, 0, bit_ALUSrcB1);
	switchbit(controlbits, 0, bit_ALUOp0);
	switchbit(controlbits, 0, bit_ALUOp1);
	switchbit(controlbits, 1, bit_PCWrite);
	switchbit(controlbits, 0, bit_PCSource0);
	switchbit(controlbits, 0, bit_PCSource1);

	controlunit.ControlBits = controlbits;

	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	return STATE_registerfetch;
}

int state_registerfetch(){
	int controlbits = 0;

	switchbit(controlbits, 0, bit_ALUSrcA);
	switchbit(controlbits, 1, bit_ALUSrcB0);
	switchbit(controlbits, 1, bit_ALUSrcB1);
	switchbit(controlbits, 0, bit_ALUOp0);
	switchbit(controlbits, 0, bit_ALUOp0);

	controlunit.ControlBits = controlbits;

	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	int opcode = *controlunit.op;

	printf("OPCODE = %d\n", opcode);

	if(opcode == op_lw || opcode == op_sw)
		return STATE_computeaddress;
	else if(opcode == op_r_type)
		return STATE_execution;
	else if(opcode == op_beq)
		return STATE_branchconclusion;
	else if(opcode == op_jump)
		return STATE_jumpconclusion;
	else{
		isRunning = 0;

		// ERRO FATAL
		printf("INSTRUCAO INVALIDA.\n");

		return 0;
	}
}

int state_computeaddress(){
	int controlbits = 0;

	switchbit(controlbits, 1, bit_ALUSrcA);
	switchbit(controlbits, 0, bit_ALUSrcB0);
	switchbit(controlbits, 1, bit_ALUSrcB1);
	switchbit(controlbits, 0, bit_ALUOp0);
	switchbit(controlbits, 0, bit_ALUOp1);

	controlunit.ControlBits = controlbits;

	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	int opcode = *controlunit.op;

	if(opcode == op_lw)
		return STATE_memoryaccess_read;
	else if(opcode == op_sw)
		return STATE_memoryaccess_write;
	else{
		isRunning = 0;
		
		// ERRO FATAL
		printf("INSTRUCAO INVALIDA.\n");

		return 0;
	}
}

int state_memoryaccess_read(){
	int controlbits = 0;

	switchbit(controlbits, 1, bit_MemRead);
	switchbit(controlbits, 1, bit_IorD);

	controlunit.ControlBits = controlbits;

	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	return STATE_memreadfinish;
}

int state_memreadfinish(){
	int controlbits = 0;

	switchbit(controlbits, 0, bit_RegDst);
	switchbit(controlbits, 1, bit_RegWrite);
	switchbit(controlbits, 1, bit_MemtoReg);

	controlunit.ControlBits = controlbits;

	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	return STATE_instructionfetch;
}

int state_memoryaccess_write(){
	int controlbits = 0;

	switchbit(controlbits, 1, bit_MemWrite);
	switchbit(controlbits, 1, bit_IorD);

	controlunit.ControlBits = controlbits;


	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	return STATE_instructionfetch;
}

int state_execution(){
	int controlbits = 0;

	switchbit(controlbits, 1, bit_ALUSrcA);
	switchbit(controlbits, 0, bit_ALUSrcB0);
	switchbit(controlbits, 0, bit_ALUSrcB1);
	switchbit(controlbits, 0, bit_ALUOp0);
	switchbit(controlbits, 1, bit_ALUOp1);

	controlunit.ControlBits = controlbits;


	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	return STATE_Rconclusion;
}

int state_Rconclusion(){
	int controlbits = 0;

	switchbit(controlbits, 1, bit_RegDst);
	switchbit(controlbits, 1, bit_RegWrite);
	switchbit(controlbits, 0, bit_MemtoReg);

	controlunit.ControlBits = controlbits;

	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	return STATE_instructionfetch;
}

int state_branchconclusion(){
	int controlbits = 0;

	switchbit(controlbits, 1, bit_ALUSrcA);
	switchbit(controlbits, 0, bit_ALUSrcB0);
	switchbit(controlbits, 0, bit_ALUSrcB1);
	switchbit(controlbits, 1, bit_ALUOp0);
	switchbit(controlbits, 0, bit_ALUOp1);
	switchbit(controlbits, 1, bit_PCWriteCond);
	switchbit(controlbits, 1, bit_PCSource0);
	switchbit(controlbits, 0, bit_PCSource1);

	controlunit.ControlBits = controlbits;
	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	return STATE_instructionfetch;
}

int state_jumpconclusion(){
	int controlbits = 0;

	switchbit(controlbits, 1, bit_PCWrite);
	switchbit(controlbits, 0, bit_PCSource0);
	switchbit(controlbits, 1, bit_PCSource1);

	controlunit.ControlBits = controlbits;
	
	// Sinalizando que o controle esta pronto
	pthread_mutex_lock(&controlmutex);
	controlready = 1;
	pthread_cond_broadcast(&controlsync);
	pthread_mutex_unlock(&controlmutex);

	sem_wait(&controlunit.op_m);

	return STATE_instructionfetch;
}


void * function_controlunit(){

	pthread_mutex_init(&controlmutex, NULL);
	pthread_cond_init(&controlsync, NULL);
	controlready = 0;

	sem_init(&controlunit.op_m, 0, 0);

	// Ligacao da entrada dessa unidade funcional com a saída de onde virá os dados
	controlunit.op = &IR.output_31_26;

	int (* StateArray[])() = {
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
	};

	int CurrentState = STATE_instructionfetch;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	int clockn = 0;

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		printf("Clock #%d. PC = %d\n", clockn++, PC.output);
    	fflush(0);

		// O mux 6 recebe uma constante. Devido a implementacao
		// do mux generico, cada entrada tem um mutex, que diz
		// quando a entrada esta pronta. Ja que a entrada da
		// constante 4 do mux 6 nao recebe dados de nenhuma unidade
		// funcional, e necessario dar unlock em seu mutex a cada ciclo.
		// Esse unlock foi arbitrariamente designado responsabilidade
		// da funcao que gerencia a unidade de controle.
		sem_post(&mux6.input_m[1]);

		char c;
		if(CurrentState == STATE_registerfetch){
			CurrentState = StateArray[CurrentState]();
			//printf("\tNew state = %d\n", CurrentState);
			//scanf("%c", &c);
		}else{
			CurrentState = StateArray[CurrentState]();
			//printf("\tNew state = %d\n", CurrentState);
		}


		printf("READY CONTROL. STATE = %d\n", CurrentState);
		fflush(0);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);

		// Resetando para falso a variavel que diz que o controle nao esta pronto
		pthread_mutex_lock(&controlmutex);
		controlready = 0;
		pthread_mutex_unlock(&controlmutex);
	}
		printf("????");
    	fflush(0);
		

	if(EXITMESSAGE)
		printf("FINALIZADO: Unidade de Controle\n");
    fflush(0);

    pthread_exit(0);
}