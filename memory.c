#include "header.h"

Memory memory;

void * function_memory(){
	sem_init(&memory.Address_m, 0, 0);
	sem_init(&memory.WriteData_m, 0, 0);

	int i;

	memory.mem = (int *)malloc(2*MEMSIZE*sizeof(int));
	memory.modified = (int *)malloc(2*MEMSIZE*sizeof(int));

	for(i=0; i<2*MEMSIZE; i++)
		memory.modified[i] = 0;

	int instructionAmount = sizeof(ProgramDatabase[PROGRAMID])>>2;
	printf("AMOUNT %d\n", instructionAmount);
	// Escrevendo o programa (presente em code.c) na memoria
	for(i=0; i<instructionAmount; i++)
		memory.mem[i] = ProgramDatabase[PROGRAMID][i];

	// Ligacao das entradas dessa unidade funcional com as saidas de onde vira os dados
	memory.Address = &mux1.output;
	memory.WriteData = &B.output;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN nos sem_t das entradas
		sem_wait(&memory.Address_m);
		sem_wait(&memory.WriteData_m);

		// Espera pela unidade de controle
		pthread_mutex_lock(&controlmutex);
		while(!controlready) // p2
			pthread_cond_wait(&controlsync, &controlmutex);
		pthread_mutex_unlock(&controlmutex);

		if(controlunit.ControlBits & bit_MemRead){
			memory.MemData = memory.mem[(*memory.Address)>>2];
			printf("\t\tMemData = %x\n", memory.MemData);
			fflush(0);
		}else if(controlunit.ControlBits & bit_MemWrite){
			memory.mem[*memory.Address>>2] = *memory.WriteData;
			memory.modified[*memory.Address>>2] = 1;
		}

		// UP nos sem_t de entrada da unidade que utiliza essa saida
		sem_post(&IR.input_instruction_m);
		sem_post(&MDR.input_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Memoria\n");
    fflush(0);

    pthread_exit(0);
}