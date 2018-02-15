#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct muchlong
{
	char *num;
	unsigned long long len;
	unsigned char isNegativeBool;
} verylong;

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
			else if(a->num[0]=='0')
			{
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
	return 0;
}

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
		int i;
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
			int i;
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
			int i;
			for (i=0; i<a.len; ++i)
			{
				if (a.num[i]>b.num[i])
				{
					return 1;
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
			int i;
			for (i=0; i<a.len; ++i)
			{
				if (a.num[i]>b.num[i])
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
			int i;
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
	if (!a.isNegativeBool && b.isNegativeBool)	//teig neig
	{
		return 0;
	}
	return 1;	//neig teig
}

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
	
	for(i=0; i<sum->len; i++)
		if(sum->num[i]!=0)
		{
			carry = i;
			break;
		}
	if(carry)
	{
		for(i=0; i<sum->len-carry; i++)
			sum->num[i] = sum->num[carry+i];
		sum->len -= carry;
		sum->num = realloc(sum->num, sum->len);
		if (sum->num==NULL)
		{
			return 3;
		}
	}
	
	return 0;
}
int longMul(verylong a, verylong b, verylong *rez)
{
	int i, j, shift_count = 0;
	
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
	
	long long start = 0;
	j = 0;
	for (i = 0; i<rez->len; i++)
		if (rez->num[i]>=1 && a.num[i]<=9)
		{
			start = i;
			j = 1;
			break;
		}
	if (start)
		for(i = 0; i<=rez->len-start; i++)
			rez->num[i] = rez->num[i+start];
	rez->len = j? rez->len-start : 0;
	rez->num = realloc(rez->num, rez->len);
	if (rez->num==NULL)
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
	
	quot->isNegativeBool = (a.isNegativeBool || b.isNegativeBool) && !(a.isNegativeBool && b.isNegativeBool) ? 1 : 0;
	rem->isNegativeBool = a.isNegativeBool;
	
	if (a.len<b.len)
	{
		quot->len = 0;
		quot->num = NULL;
		
		rem->len = a.len;
		rem->num = malloc(a.len);
		memcpy(rem->num, a.num, a.len);
		
		return 0;
	}
	
	quot->len = a.len-b.len+1;
	quot->num = calloc(quot->len, 1);
	
	rem->len = 0;
	rem->num = NULL;
	
	
	
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

int print_bcdh(verylong a)
{	
	int i=0;
	if(a.isNegativeBool)
		printf("-");
	for(i=0;i<a.len;i++)
		printf("%x", a.num[i]);
	printf("\n");
	
	return 0;
}