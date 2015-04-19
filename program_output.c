#include "header.h"

void function_output_table(){

	int i;

	printf("\n");
	printf(" \033[22;31m                        Conteudo do Banco de Registradores\n\n");	
	printf(" ||     $zero | %d     ||     $t0   |  %d     ||     $s0   | %d    ||     $t8   | %d    ||\n", fileRegister.reg[0], fileRegister.reg[8], fileRegister.reg[16], fileRegister.reg[24]);
	printf(" ||     $at   | %d     ||     $t1   |  %d     ||     $s1   | %d    ||     $t9   | %d    ||\n", fileRegister.reg[1], fileRegister.reg[9], fileRegister.reg[17], fileRegister.reg[25]); 
	printf(" ||     $v0   | %d     ||     $t2   | %d     ||     $s2   | %d    ||     $k0   | %d    ||\n", fileRegister.reg[2], fileRegister.reg[10], fileRegister.reg[18], fileRegister.reg[26]);
	printf(" ||     $v1   | %d     ||     $t3   | %d     ||     $s3   | %d    ||     $k1   | %d    ||\n", fileRegister.reg[3], fileRegister.reg[11], fileRegister.reg[19], fileRegister.reg[27]);
	printf(" ||     $a0   | %d     ||     $t4   | %d     ||     $s4   | %d    ||     $gp   | %d    ||\n", fileRegister.reg[4], fileRegister.reg[12], fileRegister.reg[20], fileRegister.reg[28]);
	printf(" ||     $a1   | %d     ||     $t5   | %d     ||     $s5   | %d    ||     $sp   | %d    ||\n", fileRegister.reg[5], fileRegister.reg[13], fileRegister.reg[21], fileRegister.reg[29]);
	printf(" ||     $a2   | %d     ||     $t6   | %d     ||     $s6   | %d    ||     $fp   | %d    ||\n", fileRegister.reg[6], fileRegister.reg[14], fileRegister.reg[22], fileRegister.reg[30]);
	printf(" ||     $a3   | %d     ||     $t7   | %d     ||     $s7   | %d    ||     $ra   | %d    ||\n", fileRegister.reg[7], fileRegister.reg[15], fileRegister.reg[23], fileRegister.reg[31]);	
	

	printf("\n");
	printf(" \033[22;34m                    Conteudo dos Registradores de Controle\n\n");	
	printf("                              ||     PC     | %d     ||\n", PC.output);
	printf("                              ||     IR     | %d     ||\n", IR.output_31_26<<26 | IR.output_25_0); 
	printf(" 			      			  ||     MDR    | %d     ||\n", MDR.output);
	printf(" 		                      ||     A      | %d     ||\n", A.output);
	printf(" 			                  ||     B      | %d     ||\n", B.output);
	printf(" 			                  ||     ALUOut | %d     ||\n", ALUOut.output);

	printf("\n");
	printf(" \033[22;32m                    Conteudo Posicoes da Memoria Alteradas\n");
	printf("\n                               Posicao     Conteudo\n");
	
	for(i=0; i<2*MEMSIZE; i++){
		
		if(memory.modified[i] == 1){	// Significa que a posição na memória foi alterada

			printf("                            ||     [%d]     | %d     ||", i, memory.modified[i]);		
		}
	}
	printf("\n");
	printf("\033[22;30m\n");
}
