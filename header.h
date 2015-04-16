#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mask.h"

#define THREAD_NUMBER 20
#define MEMSIZE 1024

extern int isRunning;

extern pthread_barrier_t clocksync;
extern pthread_barrier_t controlsync;

	/*
			Unidades funcionais
									*/

// Memoria

	typedef struct memory Memory;
	extern Memory memory;
	void function_memory();

// Instruction register

	typedef struct instruction_register Instruction_register;
	extern Instruction_register IR;
	void function_instruction_register();

// Multiplexadores

	typedef struct mux Mux;
	extern Mux mux1;
	extern Mux mux2;
	extern Mux mux3;
	extern Mux mux4;
	extern Mux mux5;
	extern Mux mux6;
	void function_mux (int mask1, int mask0, Mux *mux, int *output[]);

// Logica de escrita em PC

	typedef struct or_and Or_and;
	extern Or_and OR, AND;
	void function_or_and(int flag);

// Registradores de controle

	typedef struct control_register Control_register;
	extern Control_register MDR;
	extern Control_register A;
	extern Control_register B;
	extern Control_register ALUOut;
	void function_control_register(Control_register x);

// Banco de registradores

	typedef struct file_register File_register;
	extern File_register fileRegister;
	void function_file_register();

// Unidade logica aritmetica

	typedef struct alu Alu;
	extern Alu ALU;
	void function_alu();

// ALU Control

	typedef struct alu_control Alu_control;
	extern Alu_control ALUControl;
	void function_alucontrol();

// Shift left 2

	typedef struct shift Shift;
	extern Shift shift_one;
	extern Shift shift_two;
	void function_shift();

// Registrador PC

	typedef struct pc_register Pc_register;
	extern Pc_register PC;
	void function_pc_register();

// Unidade de controle

	typedef struct controlunit ControlUnit;
	extern ControlUnit controlunit;
	void function_control_unit();

// Extensor de sinal

	typedef struct signalextend SignalExtend;
	extern SignalExtend extend;
	void function_signalextend();

// Concatenador de bits para calculo de PC

	typedef struct concatenator Concatenator;
	extern Concatenator jumpconcat;
	void function_concatenator();

	/*
			Funções auxiliares
									*/

	void function_output_table();

//comment
