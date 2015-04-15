#include "header.h"

typedef struct alu{

	// Input
	int * input_mux_one;
	int * input_mux_two;
	int * input_ALUControl;
	
	// Output
	int output_alu_result;
	int output_alu_zero;

	// Mutex
	mutex input_mux_one_m;
	mutex input_mux_two_m;
	mutex input_ALUControl_m;

}Alu;

Alu ALU;

void function_alu(){

	// Ligacao das entradas dessa unidade funcional com as saidas de onde virao os dados
	ALU.input_mux_one = &mux4.output;
	ALU.input_mux_two = &mux6.output;
	ALU.input_ALUControl = &ALUControl.output_alu;
	
	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(1){

		// DOWN nos mutex da entrada
		sem_wait(&ALU.input_mux_one_m);
		sem_wait(&ALU.input_mux_two_m);
		sem_wait(&ALU.input_ALUControl_m);

		// Bits de controle da operacao do ALU
		switch(ALU.input_ALUControl){ 
			case 0:{	//AND
				y.output_alu_result = (*y.input_mux_one) & (*y.input_mux_two);
				if(y.output_alu_result == 0)
					y.output_alu_zero = 1;
				else
					y.output_alu_zero = 0;
				break;
			}
			case 1:{	//OR
				y.output_alu_result = (*y.input_mux_one) | (*y.input_mux_two);
				if(y.output_alu_result == 0)
					y.output_alu_zero = 1;
				else
					y.output_alu_zero = 0;
				break;
			}
			case 2:{	//ADD
				y.output_alu_result = (*y.input_mux_one) + (*y.input_mux_two);
				if(y.output_alu_result == 0)
					y.output_alu_zero = 1;
				else
					y.output_alu_zero = 0;
				break;
			}
			case 6:{	//SUB
				y.output_alu_result = (*y.input_mux_one) - (*y.input_mux_two);
				if(y.output_alu_result == 0)
					y.output_alu_zero = 1;
				else
					y.output_alu_zero = 0;
				break;
			}
			case 7:{	//SLT
				y.output_alu_result = (*y.input_mux_one) < (*y.input_mux_two);
				if(y.output_alu_result == 0)
					y.output_alu_zero = 1;
				else
					y.output_alu_zero = 0;
				break;
			}
			default:
				break;
		}

		// UP nos mutex de entrada das unidades que utilizam essas saidas
		sem_post(&ALUOut.input_m);
		sem_post(&OR_AND.zero_m);
		sem_post(&mux5.input_m[0]);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}
}