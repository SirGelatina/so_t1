#include "mask.h"

typedef int semaphore;
typedef int mutex;

int executing;

extern pthread_barrier_t clocksync;

	// Memoria

typedef struct memory Memory;

extern Memory ram;

void function_memory();

