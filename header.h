#include "mask.h"

#define THREAD_NUMBER 20

typedef int semaphore;
typedef int mutex;

int executing;

extern pthread_barrier_t clocksync;
extern pthread_barrier_t controlsync;

	// Memoria

typedef struct memory Memory;
typedef struct instruction_register Instruction_register;
typedef struct mux Mux;
typedef struct or_and Or_and;
typedef struct control_register Control_register;
typedef struct file_register File_register;
typedef struct alu Alu;
typedef struct alu_control Alu_control;
typedef struct shift Shift;
typedef struct pc_register Pc_register;
typedef struct controlunit ControlUnit;
typedef struct signalextend SignalExtend;

extern Memory memory;
extern Instruction_register IR;
extern Mux mux1, mux2, mux3, mux4, mux5, mux6;
extern Or_and OR, AND;
extern Control_register MDR, A, B, ALUOut; 
extern File_register fileRegister;
extern Alu ALU;
extern Alu_control ALUControl;
extern Shift shift_one;
extern Shift shift_two;
extern PC_register PC;
extern ControlUnit controlunit;
extern SignalExtend extend;

void function_memory();
void function_instruction_register();
void function_mux (int mask1, int mask0, Mux *mux, int *output[]);
void function_or_and(int flag);
void function_control_register(Control_register x);
void function_file_register();
void function_alu();
void function_alucontrol();
void function_shift();
void function_pc_register();
void function_memory();
void function_control_unit();
void function_signalextend();

//comment
