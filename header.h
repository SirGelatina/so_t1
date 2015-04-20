#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "mask.h"

#define THREAD_NUMBER 22
#define MEMSIZE 1024

#define PROGRAMID 0
#define REGID 0

#define EXITMESSAGE 1

extern int isRunning;

extern pthread_barrier_t clocksync;

extern pthread_cond_t controlsync;
extern pthread_mutex_t controlmutex;
extern int controlready;

extern const int ProgramDatabase[][MEMSIZE];
extern void (* const InitRegister[])(int *);

extern sem_t temp;

	/*
			Unidades funcionais
									*/

// Memoria

	typedef struct memory{

		// Input
		int * Address;
		int * WriteData;

		// Output
		int MemData;
		
		// Auxiliares
		int * mem;
		int * modified;

		// sem_t
		sem_t Address_m;
		sem_t WriteData_m;

	} Memory;

	extern Memory memory;
	void * function_memory();

// Instruction register

	typedef struct instruction_register{

		// Input
		int *input_instruction;

		int buffer;

		// Output
		int output_31_26, output_25_21, output_25_0, output_20_16, output_15_0, output_15_11, output_5_0;

		// sem_t
		sem_t input_instruction_m;

	} Instruction_register;

	extern Instruction_register IR;
	void * function_instruction_register();

// Multiplexadores

	typedef struct mux{

		// Input
		int **input;

		// Output
		int output;

		// Auxiliares
		int mask1, mask0; // Mascaras usadas para separar os dois sinais de controle. Caso tenha somente um, mask1 = 0x0000;
		int input_N; // Numero de entradas do mux

		// sem_t
		sem_t * input_m;
		sem_t * output_m;

		char * name;
	} Mux;

	extern Mux mux1;
	extern Mux mux2;
	extern Mux mux3;
	extern Mux mux4;
	extern Mux mux5;
	extern Mux mux6;
	void * function_mux (void *);

// Logica de escrita em PC

	typedef struct or_and{

		// Input
		int *zero;

		// Output
		int output;

		// sem_t
		sem_t zero_m;

	} Or_and;

	extern Or_and OR_AND;
	void * function_or_and();

// Registradores de controle

	typedef struct control_register{

		// Input
		int *input;

		// Output
	    int output;

	    // Auxiliares
		int n_output; // Número de saídas

		int buffer;
		char * name;

		// sem_t	
		sem_t input_m;
		sem_t ** output_m; 	

	} Control_register;

	extern Control_register MDR;
	extern Control_register A;
	extern Control_register B;
	extern Control_register ALUOut;
	void * function_control_register(void *);

// Banco de registradores

	typedef struct file_register{

		// Input
		int *readReg1;
		int *readReg2;
		int *writeReg;
		int *writeData;

		// Output
		int readData1;
		int readData2;

		// Registradores armazenados
		int reg[32];

		// sem_t
		sem_t read_reg1_m;
		sem_t read_reg2_m;
		sem_t write_reg_m;
		sem_t write_data_m;

	} File_register;

	extern File_register fileRegister;
	void * function_fileregister();

// Unidade logica aritmetica

	typedef struct alu{

		// Input
		int * input_mux_one;
		int * input_mux_two;
		int * input_ALUControl;
		
		// Output
		int output_alu_result;
		int output_alu_zero;

		// sem_t
		sem_t input_mux_one_m;
		sem_t input_mux_two_m;
		sem_t input_ALUControl_m;

	} Alu;

	extern Alu ALU;
	void * function_alu();

// ALU Control

	typedef struct alu_control{

		// Input
		int * input_instruction;
		
		// Output
		int output_alu;

		// sem_t
		sem_t input_instruction_m;

	} Alu_control;

	extern Alu_control ALUControl;
	void * function_alucontrol();

// Shift left 2

	typedef struct shift{

		// Input
		int * input;

		// Output
		int output;

		// sem_t
		sem_t input_m;
		sem_t * output_m;

		char * name;
	} Shift;

	extern Shift shift_one;
	extern Shift shift_two;
	void * function_shift(void *);

// Registrador PC

	typedef struct pc_register{

		// Input 
		int *input, *SC;

		int buffer;

		// Output
	    int output;

	    // sem_t
		sem_t input_m, SC_m;

	} Pc_register;

	extern Pc_register PC;
	void * function_pc_register();

// Unidade de controle

	typedef struct controlunit{

		// Input
		int * op;

		// Auxiliares
		int ControlBits;

		//sem_t
		sem_t op_m;
		
	}ControlUnit;

	extern ControlUnit controlunit;
	void * function_controlunit();

// Extensor de sinal

	typedef struct signalextend{

		// Input
		int * input;

		// Output
		int output;

		// sem_t
		sem_t input_m;
	} SignalExtend;

	extern SignalExtend extend;
	void * function_signalextend();

// Concatenador de bits para calculo de PC

	typedef struct concatenator{

		// Input
		int * input_pc;
		int * input_shift;
		
		// Output
		int output;

		// sem_t
		sem_t input_pc_m;
		sem_t input_shift_m;

	} Concatenator;

	extern Concatenator jumpconcat;
	void * function_concatenator();

	/*
			Funções auxiliares
									*/

	void function_output_table();

//comment
