#include "header.h"

typedef struct or_and{

	int *input1, *input2;
	int output;

}Or_and;

Or_and or
Or_and and;

or->input1 = ;
or->input2 = &and.output;

and->input1 = ;
and->input2 = ;

/*
Functions parameters: 
	flag = 0 -> OR 
	flag = 1 -> AND 
*/
void function_or_and(int flag){

	if (flag == 0) or->output = *or->input1 | *or->input2;
	else and->output = *and->input1 & *and->input2; 

}

