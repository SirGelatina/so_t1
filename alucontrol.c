#include "header.h"

struct alu_control{

	// Input
	int * input_instruction;
	
	// Output
	int output_alu;

	// pthread_mutex_t
	pthread_mutex_t input_instruction_m;

};

Alu_control ALUControl;

void function_alu_control(){
	int input_alu_op;

	// Ligacao da entrada dessa unidade funcional com a saida de onde vira os dados
	ALUControl.input_instruction = &IR.output_5_0;
	
	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&ALUControl.input_instruction_m);

		input_alu_op = ((controlunit.ControlBits & 0x60) >> 5);
		// 0x60 = 0000000001100000 separa ALUOp

		if(input_alu_op == 2){	//Tipo R: ADD, SUB, AND, OR e SLT
			switch(*ALUControl.input_instruction){
				case 32:{	//ADD
					ALUControl.output_alu = 2;
					break;
				}
				case 34:{	//SUB
					ALUControl.output_alu = 6;
					break;
				}
				case 36:{	//AND
					ALUControl.output_alu = 0;
					break;
				}
				case 37:{	//OR
					ALUControl.output_alu = 1;
					break;
				}
				case 42:{	//SLT
					ALUControl.output_alu = 7;
					break;
				}
				default:
					break;
			}
		}
		else if (input_alu_op == 0){	//LW, SW
			ALUControl.output_alu = 2;
		}
		else if (input_alu_op == 1){	//BEQ
			ALUControl.output_alu = 6;
		}

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(&ALU.input_ALUControl_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}
}