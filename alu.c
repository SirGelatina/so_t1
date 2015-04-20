#include "header.h"

Alu ALU;

void * function_alu(){

	sem_init(&ALU.input_mux_one_m, 0, 0);
	sem_init(&ALU.input_mux_two_m, 0, 0);
	sem_init(&ALU.input_ALUControl_m, 0, 0);

	// Ligacao das entradas dessa unidade funcional com as saidas de onde virao os dados
	ALU.input_mux_one = &mux4.output;
	ALU.input_mux_two = &mux6.output;
	ALU.input_ALUControl = &ALUControl.output_alu;
	
	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		printf("Init ALU\n");
		fflush(0);

		// DOWN nos sem_t da entrada
		sem_wait(&ALU.input_mux_one_m);
		sem_wait(&ALU.input_mux_two_m);
		sem_wait(&ALU.input_ALUControl_m);

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

		// UP nos sem_t de entrada das unidades que utilizam essas saidas
		sem_post(&ALUOut.input_m);
		sem_post(&OR_AND.zero_m);
		sem_post(&mux5.input_m[0]);

		printf("Ready ALU\n");
		fflush(0);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: ALU\n");
    fflush(0);

    pthread_exit(0);
}