#include "header.h"

//Declarando a estrutura responsável pelo ALU
typedef struct alu{
	int * input_mux_one;
	int * input_mux_two;
	int * input_alu_control;
	
	int output_alu_result;
	int output_alu_zero;

}Alu;

//Declarando a variável que representará a unidade funcional
Alu ALU;

//Função responsável por controlar a unidade funcional
void function_alu(){
	
	pthread_barrier_wait(&clocksync);

	while(1){
		switch(*y.input_alu_control){
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

		pthread_barrier_wait(&clocksync);
	}
}