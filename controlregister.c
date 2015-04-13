#include "header.h" 

/*---------------- REGISTRADORES DE CONTROLE... ----------------*/
typedef struct control_register{

	int *input;
       	int output;	
}Control_register;

Control_register PC, MDR, A, B, ALUOut; // IR não está incluso, pois é tratado separadamente (instructionregister)

void function_control_register(Control_register x){
		
	// Inicialização dos registradores
	PC.input = &mux5.output; PC.output = 0;
	MDR.input = &memory.MemData; MDR.output = NULL;
	A.input = &fileRegister.readData1; A.output = NULL;
	B.input = &fileRegister.readData2; B.output = 0;
	ALUOut.input = &ALU.output; ALUOut.output = NULL;
	
	pthread_barrier_wait(&clocksync);

	// Execução da função
	while(1){

		x.output = &x.input;
	}
	pthread_barrier_wait(&clocksync)
}

