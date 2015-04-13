#include "header.h"

typedef struct memory{
	int * Address;
	int * WriteData;

	int * mem;

	mutex Address_m;
	mutex WriteData_m;

	int MemData;
} Memory;

Memory ram;

void function_memory(){

	pthread_barrier_wait(&clocksync);

	while(1){

	}
}