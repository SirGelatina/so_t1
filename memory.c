#include "header.h"

struct memory{

	// Input
	int * Address;
	int * WriteData;

	// Output
	int MemData;
	
	// Auxiliares
	int * mem;
	int * modified;

	// pthread_mutex_t
	pthread_mutex_t Address_m;
	pthread_mutex_t WriteData_m;

};

Memory memory;

void function_memory(){

	memory.Address = &mux1.output;
	memory.WriteData = &B.output;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){

		// DOWN nos pthread_mutex_t das entradas
		pthread_mutex_lock(&memory.Address_m);
		pthread_mutex_lock(&memory.WriteData_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&controlsync);

		if(controlunit.ControlBits & separa_MemRead)
			memory.MemData = memory.mem[*memory.Address];
		else if(controlunit.ControlBits & separa_MemWrite)
			memory.mem[*memory.Address] = *memory.WriteData;

		// UP nos pthread_mutex_t de entrada da unidade que utiliza essa saida
		pthread_mutex_unlock(&IR.input_instruction_m);
		pthread_mutex_unlock(&MDR.input_m);

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);
	}
}