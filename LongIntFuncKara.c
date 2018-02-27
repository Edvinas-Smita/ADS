#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LongIntegerHeader.h"
#define BASE 10

//{ func declarations

//}

//{ free & read
void freeStruct(verylong *a)
{
	if (a!=NULL)
	{
		if (a->num!=NULL)
		{
			free(a->num);
		}
		a->len = 0;
		a->isNegativeBool = 0;
	}
}
int readToStruct(FILE *input, verylong *a)
{
	unsigned long long i;
	
	a->num = NULL;
	a->isNegativeBool = 0;
	for(i = 0;; i++)
	{
		a->num = realloc(a->num, i+1);
		a->num[i] = getc(input);
		if(a->num[i]==0xA || a->num[i]==0xFF || a->num[i]=='	' || a->num[i]==' ')
		{
			a->num[i] = 0;
			if(i!=0)
				break;
			i = -1;
		}
		else if(a->num[i]==0xD)
		{
			i--;
		}
		else if(!i)
		{
			if(a->num[0]=='+' || a->num[0]=='-')
			{
				a->isNegativeBool=a->num[0]=='-'?a->isNegativeBool?0:1:0;
				i=-1;
			}
		}
		else if(!(a->num[i]>='0' && a->num[i]<='9'))
		{
			printf("Enter a number pretty please!\n");
			a->isNegativeBool=0;
			while(getc(input)!=0xA);
			i=-1;
		}
		if(a->num[i]>='0' && a->num[i]<='9')
			a->num[i]-=0x30;
	}
	a->len=i;
	if (removeLeadingZeros(a))
	{
		return 1;
	}
	return 0;
}
//}

//{ comparison
int longIsEqual(verylong a, verylong b)
{
	if (!(a.len || b.len))
	{
		return 1;
	}
	if (a.num==NULL || b.num==NULL)
	{
		return 0;
	}
	if (a.len==b.len && a.isNegativeBool==b.isNegativeBool)
	{
		long long i;
		for (i=0; i<a.len; ++i)
		{
			if (a.num[i]!=b.num[i])
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
int longIsGreater(verylong a, verylong b)
{
	if (!(a.len || b.len))
	{
		return 0;
	}
	if (a.num==NULL || b.num==NULL)
	{
		return 0;
	}
	if (a.isNegativeBool && b.isNegativeBool)	//neig neig
	{
		if (a.len<b.len)
		{
			return 1;
		}
		if (a.len>b.len)
		{
			return 0;
		}
		if (a.len==b.len)
		{
			long long i;
			for (i=0; i<a.len; ++i)
			{
				if (a.num[i]<b.num[i])
				{
					return 1;
				}
			}
			return 0;
		}
	}
	if (!a.isNegativeBool && !b.isNegativeBool)	//teig teig
	{
		if (a.len>b.len)
		{
			return 1;
		}
		if (a.len<b.len)
		{
			return 0;
		}
		if (a.len==b.len)
		{
			long long i;
			for (i=0; i<a.len; ++i)
			{
				if (a.num[i]>b.num[i])
				{
					return 1;
				}
				else if (a.num[i]<b.num[i])
				{
					return 0;
				}
			}
			return 0;
		}
	}
	if (!a.isNegativeBool && b.isNegativeBool)	//teig neig
	{
		return 1;
	}
	return 0;	//neig teig
}
int longIsLess(verylong a, verylong b)
{
	if (!(a.len || b.len))
	{
		return 0;
	}
	if (a.num==NULL || b.num==NULL)
	{
		return 0;
	}
	if (a.isNegativeBool && b.isNegativeBool)	//neig neig
	{
		if (a.len>b.len)
		{
			return 1;
		}
		if (a.len<b.len)
		{
			return 0;
		}
		if (a.len==b.len)
		{
			long long i;
			for (i=0; i<a.len; ++i)
			{
				if (a.num[i]>b.num[i])
				{
					return 0;
				}
				else if (a.num[i]<b.num[i])
				{
					return 1;
				}
			}
			return 0;
		}
	}
	if (!a.isNegativeBool && !b.isNegativeBool)	//teig teig
	{
		if (a.len<b.len)
		{
			return 1;
		}
		if (a.len>b.len)
		{
			return 0;
		}
		if (a.len==b.len)
		{
			long long i;
			for (i=0; i<a.len; ++i)
			{
				if (a.num[i]>b.num[i])
				{
					return 0;
				}
				else if (a.num[i]<b.num[i])
				{
					return 1;
				}
			}
			return 0;
		}
	}
	if (!a.isNegativeBool && b.isNegativeBool)	//teig neig
	{
		return 0;
	}
	return 1;	//neig teig
}
//}

//{ aritmetic
int longSum(verylong a, verylong b, verylong *sum)
{
	unsigned long long i, carry = 0;
	
	sum->len = a.len > b.len ? a.len+1 : b.len+1;
	sum->num = calloc(sum->len, 1);
	if (sum->num==NULL)
	{
		return 2;
	}
	
	if (!a.isNegativeBool && !b.isNegativeBool)	//teigiamas+teigiamas
	{
		for (i=1; i <= sum->len; ++i)
		{
			sum->num[sum->len-i] = (i<=a.len ? a.num[a.len-i] : 0) + (i<=b.len ? b.num[b.len-i] : 0);
			if(carry)
			{
				carry = 0;
				sum->num[sum->len-i]++;
			}
			if(sum->num[sum->len-i] > 9)
			{
				sum->num[sum->len-i] -= 10;
				carry = 1;
			}
		}
		sum->isNegativeBool = 0;
	}
	else if(!a.isNegativeBool && b.isNegativeBool)	//teigiamas+neigiamas
	{
		for(i=1; i<=sum->len; i++)
		{
			sum->num[sum->len-i] = (i<=a.len ? a.num[a.len-i] : 0) - (i<=b.len ? b.num[b.len-i] : 0);
			if(carry)
			{
				carry = 0;
				sum->num[sum->len-i]--;
			}
			if(sum->num[sum->len-i]<0)
			{
				sum->num[sum->len-i] += 10;
				carry = 1;
			}
		}
		sum->isNegativeBool=carry;
		if(carry)
		{
			sum->num[sum->len-1]=10-sum->num[sum->len-1];
			for(i=0; i<sum->len-1; i++)
				sum->num[i] = 9-sum->num[i];
		}
	}
	else if(a.isNegativeBool && !b.isNegativeBool)	//neigiamas+teigiamas
	{
		for(i=1; i<=sum->len; i++)
		{
			sum->num[sum->len-i] = -(i<=a.len ? a.num[a.len-i] : 0) + (i<=b.len ? b.num[b.len-i] : 0);
			if(carry)
			{
				carry = 0;
				sum->num[sum->len-i]--;
			}
			if(sum->num[sum->len-i]<0)
			{
				sum->num[sum->len-i]+=10;
				carry = 1;
			}
		}
		sum->isNegativeBool=carry;
		if(carry)
		{
			sum->num[sum->len-1] = 10 - sum->num[sum->len-1];
			for(i=0; i<sum->len-1; i++)
				sum->num[i] = 9-sum->num[i];
		}
	}
	else if(a.isNegativeBool && b.isNegativeBool)		//neigiamas+neigiamas
	{
		for(i=1; i<=sum->len; i++)
		{
			sum->num[sum->len-i] = (i<=a.len ? a.num[a.len-i] : 0) + (i<=b.len ? b.num[b.len-i] : 0);
			if(carry)
			{
				carry = 0;
				sum->num[sum->len-i]++;
			}
			if(sum->num[sum->len-i]>9)
			{
				sum->num[sum->len-i] -= 10;
				carry = 1;
			}
		}
		sum->isNegativeBool=1;
	}
	
	if (removeLeadingZeros(sum))
	{
		return 1;
	}
	
	return 0;
}
int longMul(verylong a, verylong b, verylong *rez)
{
	if (a.len==0 || b.len==0)
	{
		rez->len = 0;
		rez->num = NULL;
		rez->isNegativeBool = 0;
	}
	rez->len = (a.len && b.len)? a.len + b.len : 0;
	rez->num = calloc(rez->len, 1);
	if (rez->num==NULL)
	{
		return 2;
	}
	rez->isNegativeBool=0;
	
	if ((a.isNegativeBool || b.isNegativeBool) && !(a.isNegativeBool && b.isNegativeBool))
	{
		rez->isNegativeBool = 1;
	}
	
	long long i, j, shift_count = 0;
	for (i = b.len-1; i>=0; i--)
	{
		for (j = rez->len-1; j>=0; j--)
		{
			if (j>=b.len)
				rez->num[j - shift_count ] += a.num[j-b.len] * b.num[i];
			rez->num[j-1] += rez->num[j]/10;
			rez->num[j] %= 10;
		}
		shift_count++;
	}
	
	if (removeLeadingZeros(rez))
	{
		return 3;
	}
	
	return 0;
}

int left_shift(verylong *a, long long count)
{
	long long old_length = a->len;
	long long i;
	a->num = realloc(a->num, a->len + count);
	if(a->num == NULL) return -1;
	a->len += count;
	
	for(i = old_length; i < a->len; i++)
		a->num[i] = 0;
	return 0;
}

int longMul_karatsuba_rec(verylong a, verylong b, verylong *rez)
{
	//printf("Allocating memory for product's number array... ");
	freeStruct(rez);
	rez->num = malloc(sizeof(a.len+b.len + 1));
	if(rez->num == NULL) return -1;
	//printf("Done.\n");
	
	if( a.len <= 1 || b.len <= 1){
			//printf("Calling ordinary mull... ");
			if( longMul(a,b,rez) ) return -1;
			//printf("Done.\n");
			return 0;
	}
	//printf("Declaring variables... ");
	long long m = longIsGreater(a,b) ? b.len/2  :a.len/2 ;
	
	//m = ceil(m);
	long long i,j=0;
	
	verylong number_part_a1, number_part_a2;
	verylong number_part_b1, number_part_b2;
	
	verylong z0, z1, z2;
	verylong sum_a1_a2, sum_b1_b2;
	
	verylong sum_z1_z2;
	verylong sum_z1z2_z0;
	verylong z0_z2_negSum;
	
	number_part_a2.len = m;
	number_part_a1.len = a.len - m;
	number_part_b2.len = m;
	number_part_b1.len = b.len - m;
	
	
	
	number_part_a1.num = malloc(number_part_a1.len);
		if (number_part_a1.len && number_part_a1.num == NULL) return -1; 
	number_part_a2.num = malloc(number_part_a2.len);
		if (number_part_a2.len && number_part_a2.num == NULL) return -1; 
	number_part_b1.num = malloc(number_part_b1.len);
		if (number_part_b1.len && number_part_b1.num == NULL) return -1; 	
	number_part_b2.num = malloc(number_part_b2.len);
		if (number_part_b2.len && number_part_b2.num == NULL) return -1; 	
	
	number_part_a1.isNegativeBool = 0;
	number_part_a2.isNegativeBool = 0;
	number_part_b1.isNegativeBool = 0;
	number_part_b2.isNegativeBool = 0;
	z0.isNegativeBool = 0;
	z1.isNegativeBool = 0;
	z2.isNegativeBool = 0;
	sum_a1_a2.isNegativeBool = 0;
	sum_b1_b2.isNegativeBool = 0;
	sum_z1_z2.isNegativeBool = 0;
	sum_z1z2_z0.isNegativeBool = 0;
	//printf("Done.\n");
	

	/*
	for(i=0;i<m;i++){
		number_part_a1.num[i] = a.num[i]; // example of -69 IQ
		number_part_b1.num[i] = b.num[i];
	}
	for(i=m;i<a.len;i++)
		number_part_a2.num[j++] = a.num[i];
		j = 0;
	for(i=m;i<b.len;i++)
		number_part_b2.num[j++] = b.num[i];
	*/
	
	//printf("Splitting operands... ");
	j = number_part_a2.len - 1;
	for(i=a.len-1;i>a.len-1-m;i--)
		number_part_a2.num[j--] = a.num[i];
	j = number_part_a1.len - 1;
	for(i=a.len-1-m;i>=0;i--)
		number_part_a1.num[j--] = a.num[i];

	j = number_part_b2.len - 1;
	for(i=b.len-1;i>b.len-1-m;i--)
		number_part_b2.num[j--] = b.num[i];
	j = number_part_b1.len - 1;
	for(i=b.len-1-m;i>=0;i--)
		number_part_b1.num[j--] = b.num[i];
	//printf("Done\n");
		

	
	//printf("Summing a1 and a2, b1 and b2...");
	if( longSum(number_part_a1,number_part_a2,&sum_a1_a2) ) return -1;
	if( longSum(number_part_b1,number_part_b2,&sum_b1_b2)) return -1;
	//printf("Done.\n");
		
	//printf("Recursive calls... ");
	if( longMul_karatsuba(number_part_a1, number_part_b1, &z2) ) return -1;
	if( longMul_karatsuba(number_part_a2, number_part_b2, &z0) ) return -1;
	if( longMul_karatsuba(sum_a1_a2, sum_b1_b2, &z1) ) return -1;
	//printf("Done recursion.\n");
	
	freeStruct(&number_part_a1);
	freeStruct(&number_part_a2);
	freeStruct(&number_part_b1);
	freeStruct(&number_part_b2);


	

	//printf("Negsum calculation... ");
	if (longSum(z0,z2,&z0_z2_negSum) ) return -1;
	z0_z2_negSum.isNegativeBool = 1;
	//printf("Done.\n");
	
	//printf("Subtracting from z1... ");
	char *z1numCopy = z1.num;
	if (longSum(z1,z0_z2_negSum,&z1) ) return -1;
	free(z1numCopy);
	//printf("Done.\n");

	//printf("Left shifts... ");
	if (left_shift(&z1,m) ) return -1;
	if (left_shift(&z2,2*m) ) return -1;
	//printf("Done.\n");

	
	//printf("Summing z1, z2 ,z0... ");
	if( longSum(z1,z2,&sum_z1_z2) ) return -1;
	
	freeStruct(rez);
	
	if (longSum(sum_z1_z2,z0,rez) ) return -1;
	//printf("All done.\n\n");

	freeStruct(&z0);
	freeStruct(&z1);
	freeStruct(&z2);
	freeStruct(&sum_a1_a2);
	freeStruct(&sum_b1_b2);
	freeStruct(&sum_z1_z2);
	freeStruct(&z0_z2_negSum);
	
	
	
	return 0;
}

int longMul_karatsuba(verylong a, verylong b, verylong *rez)
{
	rez->len = 0;
	rez->isNegativeBool = 0;
	rez->num = NULL;
	if (longMul_karatsuba_rec(a, b, rez) )
	{
		return -1;
	}
}


static long long much = 0;
void dummy()
{
	much++;
	printf("much %d\n",much);
	dummy();
}


int longDiv(verylong a, verylong b, verylong *quot, verylong *rem)
{
	if (b.len==0)
	{
		return 1;
	}
	
	if (a.len<b.len)
	{
		quot->len = 0;
		quot->num = NULL;
		quot->isNegativeBool = 0;
		
		rem->len = a.len;
		rem->isNegativeBool = a.isNegativeBool;
		rem->num = malloc(a.len);
		memcpy(rem->num, a.num, a.len);
		
		return 0;
	}
	
	quot->isNegativeBool = 0;
	quot->len = a.len-b.len+1;
	quot->num = calloc(quot->len, 1);
	
	rem->len = 0;
	rem->num = NULL;
	
	long long i;
	verylong compare;
	char doDouble, aNeg = a.isNegativeBool, bNeg = b.isNegativeBool;
	a.isNegativeBool = b.isNegativeBool = 0;
	for (i = 0; i<quot->len; i++)
	{
		quot->num[i] = 5;
		doDouble = 1;
		if (longMul(b, *quot, &compare))
		{
			return 1;
		}
		while (1)
		{
			if (longIsEqual(a, compare))
			{
				return 0;
			}
			else if (longIsLess(compare, a))	//reikia didinti
			{
				freeStruct(&compare);
				if (quot->num[i]==1 || quot->num[i]==2 || quot->num[i]==4 || quot->num[i]==6 || quot->num[i]==9)
				{
					break;
				}
				quot->num[i] += doDouble ? 2 : 1;
				doDouble = 0;
				if (longMul(b, *quot, &compare))
				{
					return 1;
				}
			}
			else if (longIsGreater(compare, a))		//reikia mazinti
			{
				freeStruct(&compare);
				if (quot->num[i]==1 || quot->num[i]==4 || quot->num[i]==6 || quot->num[i]==8 || quot->num[i]==9)
				{
					--quot->num[i];
					break;
				}
				quot->num[i] -= doDouble ? 2 : 1;
				doDouble = 0;
				if (longMul(b, *quot, &compare))
				{
					return 1;
				}
			}
		}
	}
	
	a.isNegativeBool = aNeg;
	b.isNegativeBool = bNeg;
	quot->isNegativeBool = (a.isNegativeBool || b.isNegativeBool) && !(a.isNegativeBool && b.isNegativeBool) ? 1 : 0;
	if (removeLeadingZeros(quot))
	{
		return 1;
	}
	if (longMul(b, *quot, &compare))
	{
		return 1;
	}
	compare.isNegativeBool = compare.isNegativeBool ? 0 : 1;
	if (longSum(a, compare, rem))
	{
		return 1;
	}
	
	return 0;
}
int longExp(verylong a, verylong b, verylong *exp)
{
	exp->isNegativeBool = 0;
	exp->len = 0;
	exp->num = NULL;
	printf("Nothing here yet!");
	
	return 0;
}
//}

//{ other
int removeLeadingZeros(verylong *a)
{
	long long i, start = 0;
	char notZeroLen = 0;
	for (i = 0; i<a->len; i++)
	{
		if (a->num[i]>=1 && a->num[i]<=9)
		{
			start = i;
			notZeroLen = 1;
			break;
		}
	}
	if (start)
	{
		for(i = 0; i<=a->len-start; i++)
		{
			a->num[i] = a->num[i+start];
		}
	}
	a->len = notZeroLen ? a->len-start : 0;
	a->num = realloc(a->num, a->len);
	if (a->num==NULL && a->len!=0)
	{
		return 1;
	}
	return 0;
}
int print_bcdh(verylong a)
{	
	long long i;
	if(a.isNegativeBool)
		printf("-");
	for(i=0;i<a.len;i++)
		printf("%x", a.num[i]);
	printf("\n");
	
	return 0;
}
//}
