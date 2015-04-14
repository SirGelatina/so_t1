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

/*------------------------------------------------------------------------------------------------*/ 
//	         Correspodência entre registradores e posicao no vetor 'reg' de File_register     
//
//     ||     $zero | 0     ||     $t0   | 8     ||     $s0   | 16    ||     $t0   | 24    ||              
//     ||     $at   | 1     ||     $t1   | 9     ||     $s1   | 17    ||     $t0   | 25    || 
//     ||     $v0   | 2     ||	   $t2   | 10    ||     $s2   | 18    ||     $t0   | 26    || 
//     ||     $v1   | 3     ||     $t3   | 11    ||     $s3   | 19    ||     $t0   | 27    || 
//     ||     $a0   | 4     ||     $t4   | 12    ||     $s4   | 20    ||     $t0   | 28    || 
//     ||     $a1   | 5     ||     $t5   | 13    ||     $s5   | 21    ||     $t0   | 29    || 
//     ||     $a2   | 6     ||     $t6   | 14    ||     $s6   | 22    ||     $t0   | 30    || 
//     ||     $a3   | 7     ||     $t7   | 15    ||     $s7   | 23    ||     $t0   | 31    || 
// 	  	    	
/*------------------------------------------------------------------------------------------------*/

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

		x.readData1 = x.readReg1;
		x.readData2 = x.readReg2;
		x.reg[writeReg] = x.writeData;
	}
	pthread_barrier_wait(&clocksync);
}


