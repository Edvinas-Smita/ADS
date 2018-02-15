#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct muchlong
{
	char *num;
	unsigned long long len;
	unsigned char isNegativeBool;
} verylong;
//{ func declarations
void freeStruct(verylong *a);
int readToStruct(FILE *input, verylong *a);
int longIsEqual(verylong a, verylong b);
int longIsGreater(verylong a, verylong b);
int longIsLess(verylong a, verylong b);
int longSum(verylong a, verylong b, verylong *sum);
int longMul(verylong a, verylong b, verylong *mul);
int longDiv(verylong a, verylong b, verylong *quot, verylong *div);
int longExp(verylong a, verylong b, verylong *exp);
int removeLeadingZeros(verylong *a);
int print_bcdh(verylong a);
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

