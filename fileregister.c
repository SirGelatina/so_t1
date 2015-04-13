#include "header.h"

/*---------------- BANCO DE REGISTRADORES ----------------*/
typedef struct file_register{

	int readReg1;
	int readReg2;
	int writeReg;
	int writeData;
	int readData1;
	int readData2;
	int reg[32];
}File_register;

File_register fileRegister;

void function_file_register(File_register x){

	// Inicialização dos registradores
	int i;

	for(i=0; i<32; i++){
		x->reg[i] = 0;
	}

	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(1){

		x->readData1 = readReg1;
		x->readData2 = readReg1;
		x->writereg = writeData;
	}
	pthread_barrier_wait(&clocksync);
}


