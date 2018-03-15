//Autoriai: Šmita Edvinas ir Šaulys Teodoras - VU MIF PS 1k. 2gr. 2pogr. 2017-2018m.m.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LongIntegerHeader.h"

//{ private funcion declarations
int removeLeadingZeros(verylong *a);
//int recursivePowerOfTwoExponent(verylong *powers, unsigned long long b, unsigned long long lastFound, verylong *exp);
//}

//{ free & read
void freeStruct(verylong *a)
{
	if (a!=NULL)
	{
		if (a->num!=NULL)
		{
			free(a->num);
			a->num = NULL;
		}
		a->len = 0;
		a->isNegativeBool = 0;
	}
}
int readToStruct(FILE *input, verylong *a)
{
	unsigned long long i;
	
	a->len = 1;
	a->num = calloc(1, 1);
	if (a->num == NULL)
	{
		return -1;
	}
	a->isNegativeBool = 0;
	for(i = 0;; ++i)
	{
		a->num = realloc(a->num, i+1);
		if (a->num == NULL)
		{
			return -1;
		}
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
		else if(!(a->num[i]>='0' && a->num[i]<='9'))
		{
			if(i == 0 && (a->num[0]=='+' || a->num[0]=='-'))
			{
				a->isNegativeBool=a->num[0]=='-'?a->isNegativeBool?0:1:0;
				i=-1;
			}
			else
			{
				return 1;
				/*printf("Enter a number pretty please!\n");
				a->isNegativeBool=0;
				while(getc(input)!=0xA);
				i=-1;*/
			}
		}
		else
		{
			a->num[i]-=0x30;
		}
	}
	a->len=i;
	return removeLeadingZeros(a);
}
//}

//{ comparison
int verylongA_EQUALS_verylongB_Bool(verylong a, verylong b)
{
	if (a.len == 0 || a.num == NULL || b.len == 0 || b.num == NULL)
	{
		return 0;
	}
	if (a.len==b.len && a.isNegativeBool==b.isNegativeBool)
	{
		unsigned long long i;
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
int verylongA_IS_GREATER_THAN_verylongB_Bool(verylong a, verylong b)
{
	if (a.len == 0 || a.num == NULL || b.len == 0 || b.num == NULL)
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
			unsigned long long i;
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
			unsigned long long i;
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
int verylongA_IS_LESS_THAN_verylongB_Bool(verylong a, verylong b)
{
	if (a.len == 0 || a.num == NULL || b.len == 0 || b.num == NULL)
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
			unsigned long long i;
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
			unsigned long long i;
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

int verylongA_EQUALS_longlongB_Bool(verylong a, long long b, int treatAsSignedBool)
{
	if (a.len == 0 || a.num == NULL)
	{
		return 0;
	}
	if (a.len == 1 && a.num[0] == 0 && b == 0)
	{
		return 1;
	}
	char bLen;
	unsigned long long bCopy = (unsigned long long) b;
	if (treatAsSignedBool)
	{
		for (bLen = 1; ;++bLen)
		{
			if ((b /= 10) == 0)
			{
				break;
			}
		}
		b = (long long) bCopy;
	}
	else
	{
		for (bLen = 1; ;++bLen)
		{
			if ((bCopy /= 10) == 0)
			{
				break;
			}
		}
	}
	
	if (a.len != bLen)
	{
		return 0;
	}
	if (!treatAsSignedBool)
	{
		unsigned long long aInLLU;
		if (castVerylongToULongLong(a, &aInLLU))
		{
			return 0;
		}
		if (aInLLU == (unsigned long long) b)
		{
			return 1;
		}
		return 0;
	}
	
	if ((a.isNegativeBool && b < 0) || (!a.isNegativeBool && b > 0))
	{
		char i;
		if (b < 0)
		{
			b = -b;
		}
		for (i=bLen - 1; i > 0; --i)
		{
			if (a.num[i] != b % 10)
			{
				return 0;
			}
			b /= 10;
		}
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}
int verylongA_IS_GREATER_THAN_longlongB_Bool(verylong a, long long b, int treatAsSignedBool)
{
	if (a.len == 0 || a.num == NULL)
	{
		return 0;
	}
	char bLen;
	unsigned long long bCopy = (unsigned long long) b;
	if (treatAsSignedBool)
	{
		for (bLen = 1; ;++bLen)
		{
			if ((b /= 10) == 0)
			{
				break;
			}
		}
		b = (long long) bCopy;
	}
	else
	{
		for (bLen = 1; ;++bLen)
		{
			if ((bCopy /= 10) == 0)
			{
				break;
			}
		}
	}
	
	if (treatAsSignedBool)
	{
		if (a.isNegativeBool && b < 0)
		{
			if (a.len > bLen)
			{
				return 0;
			}
			else if (a.len < bLen)
			{
				return 1;
			}
			else
			{
				unsigned char i, j;
				for (i = 0; i<bLen; ++i)
				{
					bCopy = (unsigned long long) -b;
					for (j = 1; j<bLen - i; ++j)
					{
						bCopy /= 10;
					}
					if (a.num[i] > bCopy % 10)
					{
						return 0;
					}
					else if (a.num[i] < bCopy % 10)
					{
						return 1;
					}
				}
			}
		}
		else if (!a.isNegativeBool && b > 0)
		{
			if (a.len > bLen)
			{
				return 1;
			}
			else if (a.len < bLen)
			{
				return 0;
			}
			else
			{
				unsigned char i, j;
				for (i = 0; i<bLen; ++i)
				{
					bCopy = b;
					for (j = 1; j<bLen - i; ++j)
					{
						bCopy /= 10;
					}
					if (a.num[i] > bCopy % 10)
					{
						return 1;
					}
					else if (a.num[i] < bCopy % 10)
					{
						return 0;
					}
				}
			}
		}
		else if (a.isNegativeBool)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (a.len > bLen)
		{
			return 1;
		}
		else if (a.len < bLen)
		{
			return 0;
		}
		else
		{
			unsigned char i, j;
			for (i = 0; i<bLen; ++i)
			{
				bCopy = (unsigned long long) b;
				for (j = 1; j<bLen - i; ++j)
				{
					bCopy /= 10;
				}
				if (a.num[i] > bCopy % 10)
				{
					return 1;
				}
				else if (a.num[i] < bCopy % 10)
				{
					return 0;
				}
			}
		}
	}
	return 0;
}
int verylongA_IS_LESS_THAN_longlongB_Bool(verylong a, long long b, int treatAsSignedBool)
{
	if (a.len == 0 || a.num == NULL)
	{
		return 0;
	}
	char bLen;
	unsigned long long bCopy = (unsigned long long) b;
	if (treatAsSignedBool)
	{
		for (bLen = 1; ;++bLen)
		{
			if ((b /= 10) == 0)
			{
				break;
			}
		}
		b = (long long) bCopy;
	}
	else
	{
		for (bLen = 1; ;++bLen)
		{
			if ((bCopy /= 10) == 0)
			{
				break;
			}
		}
	}
	
	if (treatAsSignedBool)
	{
		if (a.isNegativeBool && b < 0)
		{
			if (a.len > bLen)
			{
				return 1;
			}
			else if (a.len < bLen)
			{
				return 0;
			}
			else
			{
				unsigned char i, j;
				for (i = 0; i<bLen; ++i)
				{
					bCopy = (unsigned long long) -b;
					for (j = 1; j<bLen - i; ++j)
					{
						bCopy /= 10;freeStruct
					}
					if (a.num[i] > bCopy % 10)
					{
						return 1;
					}
					else if (a.num[i] < bCopy % 10)
					{
						return 0;
					}
				}
			}
		}
		else if (!a.isNegativeBool && b > 0)
		{
			if (a.len > bLen)
			{
				return 0;
			}
			else if (a.len < bLen)
			{
				return 1;
			}
			else
			{
				unsigned char i, j;
				for (i = 0; i<bLen; ++i)
				{
					bCopy = b;
					for (j = 1; j<bLen - i; ++j)
					{
						bCopy /= 10;
					}
					if (a.num[i] > bCopy % 10)
					{
						return 0;
					}
					else if (a.num[i] < bCopy % 10)
					{
						return 1;
					}
				}
			}
		}
		else if (a.isNegativeBool)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (a.len > bLen)
		{
			return 0;
		}
		else if (a.len < bLen)
		{
			return 1;
		}
		else
		{
			unsigned char i, j;
			for (i = 0; i<bLen; ++i)
			{
				bCopy = b;
				for (j = 1; j<bLen - i; ++j)
				{
					bCopy /= 10;
				}
				if (a.num[i] > bCopy % 10)
				{
					return 0;
				}
				else if (a.num[i] < bCopy % 10)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

int verylongA_CAN_BE_STORED_IN_ULongLong(verylong a)
{
	if (a.len == 0 || a.num == NULL)
	{
		return 0;
	}
	unsigned long long MAX_ULongLong = -1;
	char MAX_LEN_ULongLong;
	for (MAX_LEN_ULongLong = 1; ;++MAX_LEN_ULongLong)
	{
		if ((MAX_ULongLong /= 10) == 0)
		{
			break;
		}
	}
	
	if (a.len > MAX_LEN_ULongLong)
	{
		return 0;
	}
	else if (a.len < MAX_LEN_ULongLong)
	{
		return 1;
	}
	
	unsigned char i, j;
	for (i=0; i<MAX_LEN_ULongLong; ++i)
	{
		MAX_ULongLong = -1;
		for (j=1; j<MAX_LEN_ULongLong - i; ++j)
		{
			MAX_ULongLong /= 10;
		}
		if (a.num[i] > MAX_ULongLong % 10)
		{
			return 0;
		}
		else if (a.num[i] < MAX_ULongLong % 10)
		{
			return 1;
		}
	}
	return 1;
}

int verylongA_IS_A_POWER_OF_10(verylong a)
{
	if (a.len == 0 || a.num == NULL)
	{
		return 0;
	}
	if (a.num[0] == 1)
	{
		unsigned long long i;
		for (i = 1; i < a.len; ++i)
		{
			if (a.num[i] != 0)
			{
				return 0;
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}
//}

//{ aritmetic
void invertVerylongSign(verylong *a)
{
	a->isNegativeBool = a->isNegativeBool ? 0 : 1;
}
int longSum(verylong a, verylong b, verylong *sum)
{
	if (a.len == 0 || a.num == NULL || b.len == 0 || b.num == NULL)
	{
		return -2;	//bad params
	}
	if (a.len == -1LLU || b.len == -1LLU)
	{
		return 1;
	}
	
	sum->len = a.len > b.len ? a.len+1 : b.len+1;
	sum->num = calloc(sum->len, 1);
	if (sum->num==NULL)
	{
		return -1;
	}
	
	unsigned long long i, carry = 0;
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
	
	return removeLeadingZeros(sum);
}
int longDiff(verylong a, verylong b, verylong *diff)
{
	invertVerylongSign(&b);
	return longSum(a, b, diff);
}
int longMul(verylong a, verylong b, verylong *rez)
{
	if (a.len == 0 || a.num == NULL || b.len == 0 || b.num == NULL)
	{
		return -2;	//bad params
	}
	if (a.len + b.len < a.len || a.len + b.len < b.len)
	{
		return 1;
	}
	rez->len = 1;
	rez->num = calloc(1, 1);
	if (rez->num == NULL)
	{
		return -1;
	}
	rez->isNegativeBool = 0;
	
	if ((a.len == 1 && a.num[0] == 0) || (b.len == 1 && a.num[0] == 0))
	{
		return 0;
	}
	
	if ((a.isNegativeBool || b.isNegativeBool) && !(a.isNegativeBool && b.isNegativeBool))
	{
		rez->isNegativeBool = 1;
	}
	else
	{
		rez->isNegativeBool = 0;
	}
	
	char aPowerOf10 = verylongA_IS_A_POWER_OF_10(a), bPowerOf10 = verylongA_IS_A_POWER_OF_10(b);
	if (aPowerOf10 || bPowerOf10)
	{
		rez->len = a.len + b.len - 1;
		rez->num = realloc(rez->num,rez->len);
		if (rez->num == NULL)
		{
			return -1;
		}
		if (aPowerOf10 && bPowerOf10)
		{
			rez->num[0] = 1;
		}
		else if (aPowerOf10)
		{
			memcpy(rez->num, b.num, rez->len);
		}
		else
		{
			memcpy(rez->num, a.num, rez->len);
		}
		return removeLeadingZeros(rez);
	}
	
	rez->len = a.len + b.len;
	rez->num = realloc(rez->num,rez->len);	
	//rez->num = calloc(rez->len, 1);
	if (rez->num == NULL)
	{
		return -1;
	}
	
	unsigned long long i, j, shift_count = 0;
 	for (i = b.len-1; i != -1LLU; i--)
 	{
 		for (j = rez->len-1; j != -1LLU; j--)
 		{
 			if (j>=b.len)
 				rez->num[j - shift_count ] += a.num[j-b.len] * b.num[i];
 			if (j > 0)
				rez->num[j-1] += rez->num[j]/10;
 			rez->num[j] %= 10;
 		}
 		shift_count++;
 	}
	
	return removeLeadingZeros(rez);
}
int longDiv(verylong a, verylong b, verylong *quot, verylong *rem)
{
	if (a.len == 0 || a.num == NULL || b.len == 0 || b.num == NULL)
	{
		return -2;	//bad params
	}
	if (b.len == 1 && b.num[0] == 0)
	{
		return 1;	//div by 0
	}
	
	quot->len = 1;
	quot->num = calloc(1, 1);
	if (quot->num == NULL)
	{
		return -1;
	}
	quot->isNegativeBool = 0;
	
	rem->len = 1;
	rem->num = calloc(1, 1);
	if (quot->num == NULL)
	{
		return -1;
	}
	rem->isNegativeBool = 0;
	
	rem->isNegativeBool = a.isNegativeBool;
	if (a.len<b.len)
	{		
		rem->len = a.len;
		rem->num = realloc(rem->num,rem->len);
		if (rem->num == NULL)
		{
			return -1;
		}
		memcpy(rem->num, a.num, a.len);
		
		quot->isNegativeBool = (a.isNegativeBool || b.isNegativeBool) && !(a.isNegativeBool && b.isNegativeBool) ? 1 : 0;
			return removeLeadingZeros(quot);
	}
	

	if (verylongA_IS_A_POWER_OF_10(b))
	{
		rem->len = b.len - 1;
		quot->len = a.len - b.len + 1;
		
		if (rem->len == 0)
		{
			rem->len = 1;
			//rem->num = calloc(1, 1);
			
			if (rem->num == NULL)
			{
				return -1;
			}
			rem->isNegativeBool = 0;
		}
		else
		{
			rem->num = realloc(rem->num,rem->len);
			if (rem->num == NULL)
			{
				return -1;
			}
			memcpy(rem->num, a.num + quot->len, rem->len);
		}
		
		quot->num = realloc(quot->num,quot->len);//siuo atveju quot len visada bus >0
		if (quot->num == NULL)
		{
			return -1;
		}
		memcpy(quot->num, a.num, quot->len);
		
		quot->isNegativeBool = (a.isNegativeBool || b.isNegativeBool) && !(a.isNegativeBool && b.isNegativeBool) ? 1 : 0;
			return removeLeadingZeros(quot);
	}
	//printf("pow 10 end\n");
	
	quot->len = a.len - b.len + 1;
	quot->num = realloc(quot->num,quot->len);
	if (quot->num == NULL)
	{
		return -1;
	}
	
	
	unsigned long long i;
	verylong compare = {NULL, 1, 0};
	char doDouble, aNeg = a.isNegativeBool, bNeg = b.isNegativeBool;
	a.isNegativeBool = b.isNegativeBool = 0;
	
	for (i = 0; i<quot->len; i++)
	{
		quot->num[i] = 5;
		doDouble = 1;
		freeStruct(&compare);
		if (longMul(b, *quot, &compare))
		{
			return 2;
		}
		
		while (1)
		{
			if (verylongA_EQUALS_verylongB_Bool(a, compare))
			{
				freeStruct(&compare);
				
				quot->isNegativeBool = (a.isNegativeBool || b.isNegativeBool) && !(a.isNegativeBool && b.isNegativeBool) ? 1 : 0;
				
				removeLeadingZeros(quot);
				return removeLeadingZeros(rem);
			}
			else if (verylongA_IS_LESS_THAN_verylongB_Bool(compare, a))	//reikia didinti
			{
				if (quot->num[i]==1 || quot->num[i]==2 || quot->num[i]==4 || quot->num[i]==6 || quot->num[i]==9)
				{
					break;
				}
				quot->num[i] += doDouble ? 2 : 1;
			}
			else if (verylongA_IS_GREATER_THAN_verylongB_Bool(compare, a))		//reikia mazinti
			{
				if (quot->num[i]==1 || quot->num[i]==4 || quot->num[i]==6 || quot->num[i]==8 || quot->num[i]==9)
				{
					--quot->num[i];
					break;
				}
				quot->num[i] -= doDouble ? 2 : 1;
			}
			doDouble = 0;
			freeStruct(&compare);
			if (longMul(b, *quot, &compare))
			{
				return 2;
			}
		}
		
	}
	
	a.isNegativeBool = aNeg;
	b.isNegativeBool = bNeg;
	if (removeLeadingZeros(quot))
	{
		freeStruct(&compare);
		return -1;
	}
	freeStruct(&compare);
	if (longMul(b, *quot, &compare))
	{
		return 2;
	}
	
	freeStruct(rem);
	if (longDiff(a, compare, rem))
	{
		freeStruct(&compare);
		return 2;
	}
	freeStruct(&compare);
	
	quot->isNegativeBool = (a.isNegativeBool || b.isNegativeBool) && !(a.isNegativeBool && b.isNegativeBool) ? 1 : 0;
	
	removeLeadingZeros(quot);
	return removeLeadingZeros(rem);
}
int longExp(verylong a, verylong b, verylong *exp)
{
	if (a.len == 0 || a.num == NULL || b.len == 0 || b.num == NULL)
	{
		return -2;	//bad params
	}
	if (b.isNegativeBool == 1)
	{
		return 1;
	}
	exp->len = 1;
	exp->num = calloc(1, 1);
	if (exp->num == NULL)
	{
		freeStruct(exp);
		return -1;
	}
	exp->isNegativeBool = 0;
	if (a.len == 1 && a.num[0] == 0)
	{
		return 0;
	}
	if (b.len == 1 && b.num[0] == 0)
	{
		exp->num[0] = 1;
		return 0;
	}
	
	char *leakPlug;
	exp->isNegativeBool = a.isNegativeBool ? b.num[b.len-1] % 2 == 1 ? 1 : 0 : 0;	//jei baze yra neigiama ir laipsnis nelyginis tai exponentas neigiamas
	
	if (verylongA_IS_A_POWER_OF_10(a))
	{
		if (a.len == 1)
		{
			exp->num[0] = 1;
			return 0;
		}
		verylong testlimit;
		if (castULongLongToVerylong(a.len - 1, &testlimit))
		{
			return -1;
		}
		leakPlug = testlimit.num;
		if (longMul(testlimit, b, &testlimit))
		{
			if (leakPlug != NULL)
			{
				free(leakPlug);
			}
			return 4;
		}
		if (leakPlug != NULL)
		{
			free(leakPlug);
		}
		if (castVerylongToULongLong(testlimit, &(exp->len)))
		{
			freeStruct(&testlimit);
			return 2;	//exponent is over limit
		}
		freeStruct(&testlimit);
		++exp->len;
		
		exp->num = realloc(exp->num,exp->len);
		if (exp->num == NULL)
		{
			return -1;
		}
		exp->num[0] = 1;
		return 0;
	}
	
	if (b.len == 1)
	{
		if (b.num[0] == 1)
		{
			exp->len = a.len;
			exp->num = realloc(exp->num,exp->len);
			if (exp->num == NULL)
			{
				return -1;
			}
			memcpy(exp->num, a.num, exp->len);
			return 0;
		}
		if (b.num[0] == 2)
		{
			freeStruct(exp);
			if (longMul(a, a, exp))
			{
				return 4;
			}
			return 0;
		}
		if (b.num[0] == 3)
		{
			freeStruct(exp);
			if (longMul(a, a, exp))
			{
				return 4;
			}
			leakPlug = exp->num;
			if (longMul(*exp, a, exp))
			{
				if (leakPlug != NULL)
				{
					free(leakPlug);
				}
				return 4;
			}
			if (leakPlug != NULL)
			{
				free(leakPlug);
			}
			return 0;
		}
	}
	
	unsigned long long bInLLU;
	if (castVerylongToULongLong(b, &bInLLU))
	{
		return 3;
	}
	
	exp->num[0] = 1;	//paruosiamas exponentas nes rekursyviai is jo tik daugina ir jei nebutu inicijuota i 1 tai daygybos rezultatai butu keisti
	
	verylong powers = {calloc(a.len, 1), a.len, 0};
	if (powers.num == NULL)
	{
		return -1;
	}
	
	memcpy(powers.num, a.num, a.len);
	
	if (recursivePowerOfTwoExponent(&powers, bInLLU, bInLLU, exp))
	{
		freeStruct(&powers);
		return 4;
	}
	freeStruct(&powers);
	return 0;
}
int recursivePowerOfTwoExponent(verylong *powers, unsigned long long b, unsigned long long lastFound, verylong *exp)
{
	if (lastFound == 2)
	{
		if (b == 1)
		{
			char *leakPlugBIsOne = exp->num;
			if (longMul(*powers, *exp, exp))
			{
				if (leakPlugBIsOne != NULL)
				{
					free(leakPlugBIsOne);
				}
				return 1;
			}
			if (leakPlugBIsOne != NULL)
			{
				free(leakPlugBIsOne);
			}
		}
		return 0;
	}
	unsigned long long closestPowerOf2 = 1;
	
	while ((closestPowerOf2 *= 2) < lastFound);
	if (closestPowerOf2 != b)
	{
		closestPowerOf2 /= 2;
	}
	
	printf("To calculate (b): %llu\tLast power: %llu\tNext power: %llu\n", b, lastFound, closestPowerOf2);
	
	if (recursivePowerOfTwoExponent(powers, closestPowerOf2 <= b ? b - closestPowerOf2 : b, closestPowerOf2, exp))
	{
		return 1;
	}
	char *leakPlug = powers->num;
	if (longMul(*powers, *powers, powers))		//powers laikomas kiekvienas a pakeltas dvejeto laipsniu (a^1, a^2, a^4, a^8, ...)
	{
		if (leakPlug != NULL)
		{
			free(leakPlug);
		}
		return 1;
	}
	if (leakPlug != NULL)
	{
		free(leakPlug);
	}
	if (closestPowerOf2 <= b)		//jei padauginus is a pakelto dvejeto laipsniu exponentas nebus didesnis, jei norima, tada dauginti
	{
		leakPlug = exp->num;
		if (longMul(*powers, *exp, exp))
		{
			if (leakPlug != NULL)
			{
				free(leakPlug);
			}
			return 1;
		}
		if (leakPlug != NULL)
		{
			free(leakPlug);
		}
	}
	return 0;
}
//}

//{ other
int removeLeadingZeros(verylong *a)
{
	if (a->len == 0 || a->num == NULL)
	{
		return -2;	//bad params
	}
	
	if( a->len == 1 && a->num[0] == 0 && a->isNegativeBool == 1 )
		a->isNegativeBool = 0;
		
	unsigned long long i, start = 0;
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
	a->len = notZeroLen ? a->len-start : 1;
	a->num = realloc(a->num, a->len);
	if (a->num==NULL)
	{
		return -1;
	}
	if (!notZeroLen)
	{
		a->isNegativeBool = 0;
		a->num[0] = 0;
	}
	return 0;
}
int print_bcdh(FILE *output, verylong a)
{	
	if (a.len == 0 || a.num == NULL)
	{
		return -2;	//bad params
	}
	unsigned long long i;
	if(a.isNegativeBool)
	{
		if (putc('-', output) == 0xFF)
		{
			return 1;
		}
	}
	for(i=0;i<a.len;i++)
	{
		if (putc(a.num[i] + 0x30, output) == 0xFF)
		{
			return 1;
		}
	}
	if (putc('\n', output) == 0xFF)
	{
		return 1;
	}
	printf("\n");
	
	return 0;
}
int castVerylongToULongLong(verylong a, unsigned long long *regular)
{
	if (a.len == 0 || a.num == NULL)
	{
		return -2;	//bad params
	}
	if (verylongA_CAN_BE_STORED_IN_ULongLong(a))
	{
		*regular = 0;
		char i;
		for (i = 0; i < a.len; ++i)
		{
			*regular *= 10;
			*regular += a.num[i];
		}
		return 0;
	}
	else
	{
		return 1;
	}
}
int castULongLongToVerylong(unsigned long long regular, verylong *a)
{
	a->isNegativeBool = 0;
	if (regular == 0)
	{
		a->len = 1;
		a->num = calloc(1, 1);
		return 0;
	}
	char ULL_Len, i;
	unsigned long long regCopy = (unsigned long long) regular;
	for (ULL_Len = 1; ;++ULL_Len)
	{
		if ((regCopy /= 10) == 0)
		{
			break;
		}
	}
	a->len = ULL_Len;
	a->num = calloc(a->len, 1);
	if (a->num == NULL)
	{
		return -1;
	}
	for (i = 0; i < ULL_Len; ++i)
	{
		a->num[ULL_Len-i-1] = regular % 10;
		regular /= 10;
	}
	return 0;
}
//}
