#include "header.h"

/*---------------- BANCO DE REGISTRADORES ----------------*/
typedef struct file_register{

	int *readReg1;
	int *readReg2;
	int *writeReg;
	int *writeData;
	int readData1;
	int readData2;
	int reg[32];
}File_register;

/*------------------------------------------------------------------------------------------------*/ 
//	         Correspodência entre registradores e posicao no vetor 'reg' de File_register     
//
//     ||     $zero | 0     ||     $t0   | 8     ||     $s0   | 16    ||     $t8   | 24    ||              
//     ||     $at   | 1     ||     $t1   | 9     ||     $s1   | 17    ||     $t9   | 25    || 
//     ||     $v0   | 2     ||	   $t2   | 10    ||     $s2   | 18    ||     $k0   | 26    || 
//     ||     $v1   | 3     ||     $t3   | 11    ||     $s3   | 19    ||     $k1   | 27    || 
//     ||     $a0   | 4     ||     $t4   | 12    ||     $s4   | 20    ||     $gp   | 28    || 
//     ||     $a1   | 5     ||     $t5   | 13    ||     $s5   | 21    ||     $sp   | 29    || 
//     ||     $a2   | 6     ||     $t6   | 14    ||     $s6   | 22    ||     $fp   | 30    || 
//     ||     $a3   | 7     ||     $t7   | 15    ||     $s7   | 23    ||     $ra   | 31    || 
// 	  	    	
/*------------------------------------------------------------------------------------------------*/

void function_file_register(){

	// Inicialização dos registradores
	int i;

	for(i=0; i<32; i++){
		fileRegister.reg[i] = 0;
	}

	fileRegister.readReg1 = &IR.output_25_21;
	fileRegister.readReg2 = &IR.output_20_16;
	fileRegister.writeReg = &mux2.output;
	fileRegister.writeData = &mux3.output;	

	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(1){

		fileRegister.readData1 = fileRegister.reg[fileRegister.readReg1];
		fileRegister.readData2 = fileRegister.reg[fileRegister.readReg2];
		
		fileRegister.reg[fileRegister.writeReg] = fileRegister.writeData;

		pthread_barrier_wait(&clocksync);
	}
}


