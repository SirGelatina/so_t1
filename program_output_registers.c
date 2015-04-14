void function_register_output_table(){

	printf("\n");
	printf(" \033[22;31m                        Conteudo do Banco de Registradores\n");	
	printf(" ||     $zero | %d     ||     $t0   |  %d     ||     $s0   | %d    ||     $t8   | %d    ||\n", fileReg.reg[0], fileReg.reg[8], fileReg.reg[16], fileReg.reg[24]);
	printf(" ||     $at   | %d     ||     $t1   |  %d     ||     $s1   | %d    ||     $t9   | %d    ||\n", fileReg.reg[1], fileReg.reg[9], fileReg.reg[17], fileReg.reg[25]); 
	printf(" ||     $v0   | %d     ||     $t2   | %d     ||     $s2   | %d    ||     $k0   | %d    ||\n", fileReg.reg[2], fileReg.reg[10], fileReg.reg[18], fileReg.reg[26]);
	printf(" ||     $v1   | %d     ||     $t3   | %d     ||     $s3   | %d    ||     $k1   | %d    ||\n", fileReg.reg[3], fileReg.reg[11], fileReg.reg[19], fileReg.reg[27]);
	printf(" ||     $a0   | %d     ||     $t4   | %d     ||     $s4   | %d    ||     $gp   | %d    ||\n", fileReg.reg[4], fileReg.reg[12], fileReg.reg[20], fileReg.reg[28]);
	printf(" ||     $a1   | %d     ||     $t5   | %d     ||     $s5   | %d    ||     $sp   | %d    ||\n", fileReg.reg[5], fileReg.reg[13], fileReg.reg[21], fileReg.reg[29]);
	printf(" ||     $a2   | %d     ||     $t6   | %d     ||     $s6   | %d    ||     $fp   | %d    ||\n", fileReg.reg[6], fileReg.reg[14], fileReg.reg[22], fileReg.reg[30]);
	printf(" ||     $a3   | %d     ||     $t7   | %d     ||     $s7   | %d    ||     $ra   | %d    ||\n", fileReg.reg[7], fileReg.reg[15], fileReg.reg[23], fileReg.reg[31]);	
	

	printf("\n");
	printf(" \033[22;34m                      Conteudo dos Registradores de Controle\n");	
	printf("                              ||     PC     | %d     ||\n", PC.output);
	printf("                              ||     IR     | %d     ||\n", MemData); 
	printf(" 			      ||     MDR    | %d     ||\n", MDR.output);
	printf(" 		              ||     A      | %d     ||\n", A.output);
	printf(" 			      ||     B      | %d     ||\n", B.output);
	printf(" 			      ||     ALUOut | %d     ||\n", ALUOut.output);
	printf("\033[22;30m\n");
}
