#ifndef _MASCARA_
#define _MASCARA_

/*
Posicao dos bits nos 16 sinais de controle determinados pela UC 
0-  RegDst
1-  RegWrite
2-  ALUSrcA
3-  ALUSrcB0
4-  ALUSrcB1
5-  ALUOp0
6-  ALUOp1
7-  PCSource0
8-  PCSource1
9-  PCWriteCond
10- PCWrite
11- IorD
12- MemRead
13- MemWrite
14- MemtoReg
15- IRWrite
*/

// Mascaras usadas para separar os campos dentro da instrucao

                                        // 31  26 25 21 20 16 15 11 10  6 5    0
#define bit_cop			   0xfc000000	// 111111 00000 00000 00000 00000 000000  
#define bit_rs			   0x03e00000	// 000000 11111 00000 00000 00000 000000  
#define bit_rt			   0x001f0000	// 000000 00000 11111 00000 00000 000000 
#define bit_rd             0x0000f800	// 000000 00000 00000 11111 00000 000000  
#define bit_cfuncao		   0x0000003f	// 000000 00000 00000 00000 00000 111111 
#define bit_imediato       0x0000ffff	// 000000 00000 00000   1111111111111111  
#define bit_endereco_jump  0x03ffffff   // 000000     11111111111111111111111111  

// Mascaras usadas para ativar e separar os bits do sinal de controle

#define bit_RegDst            0x0001
#define bit_RegWrite          0x0002 
#define bit_ALUSrcA           0x0004 
#define bit_ALUSrcB0          0x0008 
#define bit_ALUSrcB1          0x0010 
#define bit_ALUOp0            0x0020 
#define bit_ALUOp1            0x0040 
#define bit_ALUOp10           0x0060
#define bit_PCSource0         0x0080 
#define bit_PCSource1         0x0100 
#define bit_PCWriteCond       0x0200 
#define bit_PCWrite           0x0400 
#define bit_IorD              0x0800   
#define bit_MemRead           0x1000    
#define bit_MemWrite          0x2000     
#define bit_MemtoReg          0x4000    
#define bit_IRWrite           0x8000      

#endif
