#include <pthread.h>
#include <stdio.h>

#include "header.h"

pthread_barrier_t clocksync;

int main(){
	pthread_barrier_init(&clocksync, NULL, THREAD_NUMBER);

	/*------------ INICIALIZAÇÃO DAS UNIDADES GENÉRICAS ------------*/
	
	// Registradores de controle
	r->output = ;
	r->input = &output;
	
	// Mutexes

	// Mux
	mux1.input[0] = &PC.output;
	mux1.input[1] = &ALUOut.output;
	
}
