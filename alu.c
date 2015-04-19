#include "header.h"

Alu ALU;

void * function_alu(){

	pthread_mutex_init(&ALU.input_mux_one_m, NULL);
	pthread_mutex_init(&ALU.input_mux_two_m, NULL);
	pthread_mutex_init(&ALU.input_ALUControl_m, NULL);

	// Ligacao das entradas dessa unidade funcional com as saidas de onde virao os dados
	ALU.input_mux_one = &mux4.output;
	ALU.input_mux_two = &mux6.output;
	ALU.input_ALUControl = &ALUControl.output_alu;
	
	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN nos pthread_mutex_t da entrada
		pthread_mutex_lock(&ALU.input_mux_one_m);
		pthread_mutex_lock(&ALU.input_mux_two_m);
		pthread_mutex_lock(&ALU.input_ALUControl_m);

		// Bits de controle da operacao do ALU
		switch(*ALU.input_ALUControl){ 
			case 0:{	//AND
				ALU.output_alu_result = (*ALU.input_mux_one) & (*ALU.input_mux_two);
				if(ALU.output_alu_result == 0)
					ALU.output_alu_zero = 1;
				else
					ALU.output_alu_zero = 0;
				break;
			}
			case 1:{	//OR
				ALU.output_alu_result = (*ALU.input_mux_one) | (*ALU.input_mux_two);
				if(ALU.output_alu_result == 0)
					ALU.output_alu_zero = 1;
				else
					ALU.output_alu_zero = 0;
				break;
			}
			case 2:{	//ADD
				ALU.output_alu_result = (*ALU.input_mux_one) + (*ALU.input_mux_two);
				if(ALU.output_alu_result == 0)
					ALU.output_alu_zero = 1;
				else
					ALU.output_alu_zero = 0;
				break;
			}
			case 6:{	//SUB
				ALU.output_alu_result = (*ALU.input_mux_one) - (*ALU.input_mux_two);
				if(ALU.output_alu_result == 0)
					ALU.output_alu_zero = 1;
				else
					ALU.output_alu_zero = 0;
				break;
			}
			case 7:{	//SLT
				ALU.output_alu_result = (*ALU.input_mux_one) < (*ALU.input_mux_two);
				if(ALU.output_alu_result == 0)
					ALU.output_alu_zero = 1;
				else
					ALU.output_alu_zero = 0;
				break;
			}
			default:
				break;
		}

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(&ALUOut.input_m);
		pthread_mutex_unlock(&OR_AND.zero_m);
		pthread_mutex_unlock(&mux5.input_m[0]);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: ALU\n");
    fflush(0);

    pthread_exit(0);
}