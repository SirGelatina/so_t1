#include "header.h"

struct file_register{

	// Input
	int *readReg1;
	int *readReg2;
	int *writeReg;
	int *writeData;

	// Output
	int readData1;
	int readData2;

	// Registradores armazenados
	int reg[32];

	// Mutex
	mutex read_reg1_m;
	mutex read_reg2_m;
	mutex write_reg_m;
	mutex write_data_m;

};

File_register fileRegister;

/*------------------------------------------------------------------------------------------------*/ 
//	         Correspondência entre registradores e posicao no vetor 'reg' de File_register     
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

void * function_fileregister(void *){

	// Inicialização dos registradores
	int i;
	for(i=0; i<32; i++)
		fileRegister.reg[i] = 0;

	// Ligacao das entradas dessa unidade funcional com as saidas de onde virao os dados
	fileRegister.readReg1 = &IR.output_25_21;
	fileRegister.readReg2 = &IR.output_20_16;
	fileRegister.writeReg = &mux2.output;
	fileRegister.writeData = &mux3.output;	

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){

		// DOWN nos mutex da entrada
		sem_wait(&read_reg1_m);	
		sem_wait(&read_reg2_m);
		sem_wait(&write_reg_m);
		sem_wait(&write_data_m);	

		fileRegister.readData1 = fileRegister.reg[fileRegister.readReg1];
		fileRegister.readData2 = fileRegister.reg[fileRegister.readReg2];
		
		// If RegWrite == 1
		if(controlunit.ControlBits & separa_RegWrite != 0)
			fileRegister.reg[fileRegister.writeReg] = fileRegister.writeData;

		// UP nos mutex de entrada das unidades que utilizam essas saidas
		sem_post(&A.input_m);
		sem_post(&B.input_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}
}