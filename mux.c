#include "header.h"

Mux mux1, mux2, mux3, mux4, mux5, mux6;

/*
	0x0000, separa_IorD - mux1 
	0x0000, separa_RegDst - mux2
	0x0000, separa_MemtoReg - mux3 
	0x0000, separa_ALUSrcA - mux4 
	separa_ALUSrcB1, separa_ALUSrcB0 - mux5
	separa_PCSource1, separa_PCSource0 - mux6
*/

void * function_mux (void * arg){
	Mux * mux = (Mux *)arg;

	// Barreira para sincronizar na inicializacao de todas threads
	pthread_barrier_wait(&clocksync);

	while(isRunning){
		pthread_barrier_wait(&clocksync);

		// DOWN nos pthread_mutex_t da entrada
		int i;
		for(i = 0; i < (mux->input_N); i++)
			pthread_mutex_lock(&mux->input_m[i]);

		// Espera pela unidade de controle
		pthread_mutex_lock(&controlmutex);
		while(!controlready) // p2
			pthread_cond_wait(&controlsync, &controlmutex);
		pthread_mutex_unlock(&controlmutex);

		int bit1, bit0;

		if(mux->mask1 & controlunit.ControlBits) bit1 = 1;
		else bit1 = 0;

		if(mux->mask0 & controlunit.ControlBits) bit0 = 1;
		else bit0 = 0;

		//  bit1  |   bit0  |  resultado
		//   0    |    0    |     00
		//   0    |    1    |     01
		//   1    |    0    |     10
		//   1    |    1    |     11

		if(bit1 == 0 && bit0 == 0) mux->output = *mux->input[0];
		if(bit1 == 0 && bit0 == 1) mux->output = *mux->input[1];
		if(bit1 == 1 && bit0 == 0) mux->output = *mux->input[2];
		if(bit1 == 1 && bit0 == 1) mux->output = *mux->input[3];

		// UP nos pthread_mutex_t de entrada das unidades que utilizam essas saidas
		pthread_mutex_unlock(mux->output_m);		

		// Barreira para sincronizar no ciclo de clock atual
		pthread_barrier_wait(&clocksync);

	}

	if(EXITMESSAGE)
		printf("FINALIZADO: Multiplexador Anonimo\n");
    fflush(0);

    pthread_exit(0);
}