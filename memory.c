#include "header.h"

Memory memory;

void * function_memory(){
	pthread_mutex_init(&memory.Address_m, NULL);
	pthread_mutex_init(&memory.WriteData_m, NULL);

	int i;

	memory.mem = (int *)malloc(2*MEMSIZE*sizeof(int));
	memory.modified = (int *)malloc(2*MEMSIZE*sizeof(int));

	for(i=0; i<2*MEMSIZE; i++)
		memory.modified[i] = 0;

	int instructionAmount = sizeof(ProgramDatabase[PROGRAMID])>>2;

	for(i=0; i<instructionAmount; i++)
		memory.mem[i] = ProgramDatabase[PROGRAMID][i];

	memory.Address = &mux1.output;
	memory.WriteData = &B.output;


	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN nos pthread_mutex_t das entradas
		pthread_mutex_lock(&memory.Address_m);
		pthread_mutex_lock(&memory.WriteData_m);

		// Espera pela unidade de controle
		pthread_mutex_lock(&controlmutex);
		while(!controlready) // p2
			pthread_cond_wait(&controlsync, &controlmutex);
		pthread_mutex_unlock(&controlmutex);

		if(controlunit.ControlBits & bit_MemRead)
			memory.MemData = memory.mem[*memory.Address];
		else if(controlunit.ControlBits & bit_MemWrite){
			memory.mem[*memory.Address] = *memory.WriteData;
			memory.modified[*memory.Address] = 1;
		}

		// UP nos pthread_mutex_t de entrada da unidade que utiliza essa saida
		pthread_mutex_unlock(&IR.input_instruction_m);
		pthread_mutex_unlock(&MDR.input_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Memoria\n");
    fflush(0);

    pthread_exit(0);
}