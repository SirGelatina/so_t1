#include "header.h"

struct memory{
	int * Address;
	int * WriteData;

	pthread_mutex_t Address_m;
	pthread_mutex_t WriteData_m;

	int * mem;
	int * modified;

	int MemData;
};

Memory memory;

void function_memory(){
	memory.Address = &mux1.output;
	memory.WriteData = &B.output;

	pthread_barrier_wait(&clocksync);

	while(1){
		pthread_mutex_lock(&memory.Address_m);
		pthread_mutex_lock(&memory.WriteData_m);

		pthread_barrier_wait(&controlsync)

		if(controlunit.ControlBits & separa_MemRead)
			memory.MemData = memory.mem[*memory.Address];
		else if(controlunit.ControlBits & separa_MemWrite)
			memory.mem[*memory.Address] = *memory.WriteData;

		pthread_mutex_unlock(&IR.input_instruction_m);
		pthread_mutex_unlock(&MDR.input_m);

		pthread_barrier_wait(&clocksync)
	}
}