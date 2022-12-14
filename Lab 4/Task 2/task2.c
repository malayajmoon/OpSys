#include <stdio.h>
#include <stdlib.h>

int(*opPtrs[5]) (int a, int b);

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int subtract (int a, int b,); 
int multiply (int a, int b);
int divide (int a, int b); 
int exitProg (int a, int b); 


int main (void)
{
	/* IMPLEMENT ME: Insert your algorithm here */

	int op; 
	int op1;
	int op2;

	int(*opPtrs[]) (int, int) = {add, subtract, multiply, divide, exitProg};

	while(1){

		printf("Operand 'a': ");
		scanf("%d", &op1);

		printf("Operand 'b': ");
		scanf("%d", &op2);

		printf("Enter Operation (0 for add, 1 for subtract, 2 for multiply, 3 for divide, 4 for exit program):");
		scanf("%d", &op);

		printf("Operation Result = %d\n", ((*opPtrs[op]) (op1, op2)));
	}
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { 
	printf("Adding 'a' and 'b'\n"); 
	return a + b; 
}

int subtract (int a, int b) { 
	printf("Subtracting 'a' and 'b'\n"); 
	return a - b; 
}

int multiply (int a, int b) { 
	printf("Multiplying 'a' and 'b'\n"); 
	return a * b; 
}

int divide (int a, int b) { 
	printf("Dividing 'a' and 'b'\n"); 
	return a / b; 
}

int exitProg (int a, int b) { 
	exit(0); 
}


