#include "header.h"

struct memory{
	int * Address;
	int * WriteData;

	mutex Address_m;
	mutex WriteData_m;

	int * mem;

	int MemData;
};

Memory memory;

void function_memory(){
	memory.Address = &mux1.output;
	memory.WriteData = &B.output;

	pthread_barrier_wait(&clocksync);

	while(1){
		sem_wait(&memory.Address_m);
		sem_wait(&memory.WriteData_m);

		pthread_barrier_wait(&controlsync)

		if(controlunit.ControlBits & separa_MemRead)
			memory.MemData = memory.mem[*memory.Address];
		else if(controlunit.ControlBits & separa_MemWrite)
			memory.mem[*memory.Address] = *memory.WriteData;

		sem_post(&IR.input_instruction_m);
		sem_post(&MDR.input_m);

		pthread_barrier_wait(&clocksync)
	}
}