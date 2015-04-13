#include "mask.h"

#define THREAD_NUMBER 20

typedef int semaphore;
typedef int mutex;

int executing;

extern pthread_barrier_t clocksync;

	// Memoria

typedef struct memory Memory;

extern Memory memory;

void function_memory();

