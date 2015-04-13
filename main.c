#include <pthread.h>
#include <stdio.h>

#include "header.h"

pthread_barrier_t clocksync;

int main(){
	pthread_barrier_init(&clocksync, NULL, THREAD_NUMBER);

	
}