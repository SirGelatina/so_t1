#include "header.h"

void function_output_table(){

	int i;

	printf("\n");
	printf(" \033[22;31m                        Conteudo do Banco de Registradores\n\n");	
	printf(" ||     $zero | %5d     ||     $t0   | %5d     ||     $s0   | %5d    ||     $t8   | %5d    ||\n", fileRegister.reg[0], fileRegister.reg[8], fileRegister.reg[16], fileRegister.reg[24]);
	printf(" ||     $at   | %5d     ||     $t1   | %5d     ||     $s1   | %5d    ||     $t9   | %5d    ||\n", fileRegister.reg[1], fileRegister.reg[9], fileRegister.reg[17], fileRegister.reg[25]); 
	printf(" ||     $v0   | %5d     ||     $t2   | %5d     ||     $s2   | %5d    ||     $k0   | %5d    ||\n", fileRegister.reg[2], fileRegister.reg[10], fileRegister.reg[18], fileRegister.reg[26]);
	printf(" ||     $v1   | %5d     ||     $t3   | %5d     ||     $s3   | %5d    ||     $k1   | %5d    ||\n", fileRegister.reg[3], fileRegister.reg[11], fileRegister.reg[19], fileRegister.reg[27]);
	printf(" ||     $a0   | %5d     ||     $t4   | %5d     ||     $s4   | %5d    ||     $gp   | %5d    ||\n", fileRegister.reg[4], fileRegister.reg[12], fileRegister.reg[20], fileRegister.reg[28]);
	printf(" ||     $a1   | %5d     ||     $t5   | %5d     ||     $s5   | %5d    ||     $sp   | %5d    ||\n", fileRegister.reg[5], fileRegister.reg[13], fileRegister.reg[21], fileRegister.reg[29]);
	printf(" ||     $a2   | %5d     ||     $t6   | %5d     ||     $s6   | %5d    ||     $fp   | %5d    ||\n", fileRegister.reg[6], fileRegister.reg[14], fileRegister.reg[22], fileRegister.reg[30]);
	printf(" ||     $a3   | %5d     ||     $t7   | %5d     ||     $s7   | %5d    ||     $ra   | %5d    ||\n", fileRegister.reg[7], fileRegister.reg[15], fileRegister.reg[23], fileRegister.reg[31]);	
	

	printf("\n\n");
	printf(" \033[22;34m                       Conteudo dos Registradores de Controle\n\n");	
	printf("                             ||     PC     | %5d     ||\n", PC.output);
	printf("                             ||     IR     | %5d     ||\n", IR.output_31_26<<26 | IR.output_25_0); 
	printf("                             ||     MDR    | %5d     ||\n", MDR.output);
	printf("                             ||     A      | %5d     ||\n", A.output);
	printf("                             ||     B      | %5d     ||\n", B.output);
	printf("                             ||     ALUOut | %5d     ||\n", ALUOut.output);

	printf("\n\n");
	printf(" \033[22;32m                       Conteudo Posicoes da Memoria Alteradas\n");
	printf("\n                                 Posicao        Conteudo\n");
	
	for(i=0; i<2*MEMSIZE; i++){
		
		if(memory.modified[i] == 1){	// Significa que a posição na memória foi alterada

			printf("                           ||     [%5d]     | %5d     ||", i, memory.modified[i]);		
		}
	}
	printf("\n");
	printf("\033[22;30m\n");
}
