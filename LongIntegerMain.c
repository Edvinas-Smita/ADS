#include <stdio.h>
#include "LongIntegerHeader.h"

int main()
{
	char ch;
	verylong a, b, sum, mul;
	printf("Enter two integers:\n");
	readToStruct(stdin, &a);
	readToStruct(stdin, &b);
	
	while(1)
	{
		printf("Enter an operation to do (+, *), 0 to exit or R to reenter the integers:\n");
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
					printf("Something went wrong!\n");
					return 1;
				}
				if (print_bcdh(sum))
				{
					printf("Something went wrong!\n");
					return 1;
				}
				if (freeStruct(&sum))
				{
					printf("Something went wrong!\n");
					return 1;
				}
				break;
			}
			case '*':
			{
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Mul: ");
				if (longMul(a, b, &mul))
				{
					printf("Something went wrong!\n");
					return 1;
				}
				if (print_bcdh(mul))
				{
					printf("Something went wrong!\n");
					return 1;
				}
				if (freeStruct(&mul))
				{
					printf("Something went wrong!\n");
					return 1;
				}
				break;
			}
			case '0':
			{
				return 0;
			}
			case 'R':
			{
				if (freeStruct(&a))
				{
					printf("Something went wrong!\n");
					return 1;
				}
				if (freeStruct(&b))
				{
					printf("Something went wrong!\n");
					return 1;
				}
				readToStruct(stdin, &a);
				readToStruct(stdin, &b);
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
		
			default:
			{
				printf("Unrecognised choise!\n");
				break;
			}
		}
	}
}
