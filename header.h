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

extern Memory memory;
extern Instruction_register ir;
extern Mux mux1, mux2, mux3, mux4, mux5, mux6;
extern Or_and OR, AND;
extern Control_register PC, MDR, A, B, ALUOut;
extern File_register fileRegister;

void function_memory();
void function_instruction_register();
void function_mux (int mask1, int mask0, Mux *mux, int *output[]);
void function_or_and(int flag);
void function_control_register(Control_register x);
void function_file_register(File_register x);

