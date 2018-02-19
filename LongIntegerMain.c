#include <stdio.h>
#include "LongIntegerHeader.h"

int main()
{
	char ch;
	verylong a, b, sum, mul, quot, rem, exp;
	printf("Enter two integers:\n");
	readToStruct(stdin, &a);
	readToStruct(stdin, &b);
	
	while(1)
	{
		printf("Arithmetic:\n\t'+' Sum,\n\t'*' Multiplication,\n\t'/' Division with remainder,\n\t'^' Exponentiation;\nOther:\n\t'=' Signed compare,\n\t'a' / 'b' Print entered values,\n\t'R' Reenter integers,\n\t'0' Exit;\n");
		ch = getc(stdin);
		if (ch!=0xA && ch!=0xD && ch!=0xFF)
		{
			while(getc(stdin)!=0xA);
		}
		switch(ch)
		{
			case '+':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Sum: ");
				if (longSum(a, b, &sum))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				if (print_bcdh(sum))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				freeStruct(&sum);
				break;
			}
			case '*':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Product: ");
				if (longMul(a, b, &mul))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				
				if (print_bcdh(mul))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				
				printf("Product_karatsuba: ");
				if (longMul_karatsuba(a, b, &mul))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				
				
				if (print_bcdh(mul))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}


				
				freeStruct(&mul);
				break;
			}
			case '/':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				if (longDiv(a, b, &quot, &rem))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				
				printf("Quotient: ");
				if (print_bcdh(quot))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				printf("Remainder: ");
				if (print_bcdh(rem))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				
				freeStruct(&quot);
				freeStruct(&rem);
				break;
			}
			case '^':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Result: ");
				if (longExp(a, b, &exp))
				{
					printf("Something went wrong while calculating! Terminating...\n");
					return 1;
				}
				if (print_bcdh(exp))
				{
					printf("Something went wrong with printing the value! Terminating...\n");
					return 1;
				}
				freeStruct(&exp);
				break;
			}
			
			case '=':
			{
				if (longIsEqual(a, b))
				{
					printf("a == b\n");
				}
				if (longIsGreater(a, b))
				{
					printf("a > b\n");
				}
				if (longIsLess(a, b))
				{
					printf("a < b\n");
				}
				break;
			}
			
			case 'R':
			{
				freeStruct(&a);
				freeStruct(&b);
				readToStruct(stdin, &a);
				readToStruct(stdin, &b);
				break;
			}
			
			case 'a':
			{
				print_bcdh(a);
				break;
			}
			case 'b':
			{
				print_bcdh(b);
				break;
			}
			
			case '0':
			{
				return 0;
			}
			default:
			{
				printf("Unrecognised choise! Terminating...\n");
				break;
			}
		}
	}
}
