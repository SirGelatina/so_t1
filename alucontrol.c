#include "header.h"

//Declarando a estrutura responsável pela ALU Control
typedef struct alu_control{
	int * input_instruction;
	int * input_alu_op;
	
	int output_alu;

}Alu_control;

//Declarando a variável que representará a unidade funcional
Alu_control ALUControl;

//Função responsável por controlar a unidade funcional
void function_alu_control(){
	
	pthread_barrier_wait(&clocksync);

	while(1){
		if(*x.input_alu_op == 2){	//Tipo R: ADD, SUB, AND, OR e SLT
			switch(*x.input_instruction){
				case 32:{	//ADD
					x.output_alu = 2
					break;
				}
				case 34:{	//SUB
					x.output_alu = 6;
					break;
				}
				case 36:{	//AND
					x.output_alu = 0:
					break;
				}
				case 37:{	//OR
					x.output_alu = 1;
					break;
				}
				case 42:{	//SLT
					x.output_alu = 7;
					break;
				}
				default:
					break;
			}
		}
		else if (*x.input_alu_op == 0){	//LW, SW
			x.output_alu = 2;
		}
		else if (*x.input_alu_op == 1){	//BEQ
			x.output_alu = 6;
		}

		pthread_barrier_wait(&clocksync);
	}
}