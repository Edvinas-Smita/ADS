#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LongIntegerHeader.h"

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
		else if(!(a->num[i]>='0' && a->num[i]<='9'))
		{
			if(i == 0 && (a->num[0]=='+' || a->num[0]=='-'))
			{
				a->isNegativeBool=a->num[0]=='-'?a->isNegativeBool?0:1:0;
				i=-1;
			}
			else
			{
				printf("Enter a number pretty please!\n");
				a->isNegativeBool=0;
				while(getc(input)!=0xA);
				i=-1;
			}
		}
		else
		{
			a->num[i]-=0x30;
		}
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
int verylongA_EQUALS_verylongB_Bool(verylong a, verylong b)
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
	if (a.len == 0 && b == 0)
	{
		return 1;
	}
	char bLen;
	unsigned long long bCopy = (unsigned long long) b;
	for (bLen = 1; ;++bLen)
	{
		if ((bCopy /= 10) == 0)
		{
			break;
		}
	}
	if (a.len != bLen)
	{
		return 0;
	}
	
	if (!treatAsSignedBool || (a.isNegativeBool && b < 0) || (!a.isNegativeBool && b > 0))
	{
		unsigned char i, j;
		if (treatAsSignedBool && b < 0)
		{
			b = -b;
		}
		for (i=0; i<bLen; ++i)
		{
			bCopy = b;
			for (j=1; j<bLen - i; ++j)
			{
				bCopy /= 10;
			}
			if (a.num[i] != bCopy % 10)
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
	return 0;
}
int verylongA_IS_GREATER_THAN_longlongB_Bool(verylong a, long long b, int treatAsSignedBool)
{
	if (a.len == 0 && b == 0)
	{
		return 0;
	}
	char bLen;
	unsigned long long bCopy = (unsigned long long) b;
	for (bLen = 1; ;++bLen)
	{
		if ((bCopy /= 10) == 0)
		{
			break;
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
				for (i=0; i<bLen; ++i)
				{
					bCopy = b;
					for (j=1; j<bLen - i; ++j)
					{
						bCopy /= 10;
					}
					if (a.num[i] > bCopy % 10)
					{
						return 0;
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
				return 1;
			}
			else if (a.len < bLen)
			{
				return 0;
			}
			else
			{
				unsigned char i, j;
				for (i=0; i<bLen; ++i)
				{
					bCopy = b;
					for (j=1; j<bLen - i; ++j)
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
			for (i=0; i<bLen; ++i)
			{
				bCopy = b;
				for (j=1; j<bLen - i; ++j)
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
	if (a.len == 0 && b == 0)
	{
		return 0;
	}
	char bLen;
	unsigned long long bCopy = (unsigned long long) b;
	for (bLen = 1; ;++bLen)
	{
		if ((bCopy /= 10) == 0)
		{
			break;
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
				for (i=0; i<bLen; ++i)
				{
					bCopy = b;
					for (j=1; j<bLen - i; ++j)
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
				for (i=0; i<bLen; ++i)
				{
					bCopy = b;
					for (j=1; j<bLen - i; ++j)
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
			return 1;
		}
		else if (a.len < bLen)
		{
			return 0;
		}
		else
		{
			unsigned char i, j;
			for (i=0; i<bLen; ++i)
			{
				bCopy = b;
				for (j=1; j<bLen - i; ++j)
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
int longSum(verylong a, verylong b, verylong *sum)
{
	if (a.len == -1LLU || b.len == -1LLU)
	{
		return 1;
	}
	
	sum->len = a.len > b.len ? a.len+1 : b.len+1;
	sum->num = calloc(sum->len, 1);
	if (sum->num==NULL)
	{
		return 2;
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
	
	if (removeLeadingZeros(sum))
	{
		return 1;
	}
	
	return 0;
}
int longMul(verylong a, verylong b, verylong *rez)
{
	if (a.len == 0 || b.len == 0)
	{
		rez->len = 0;
		rez->num = NULL;
		rez->isNegativeBool = 0;
		return 0;
	}
	if (a.len + b.len < a.len || a.len + b.len < b.len)
	{
		return 1;
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
		rez->num = malloc(rez->len);
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
		return 0;
	}
	
	rez->len = a.len + b.len;
	rez->num = calloc(rez->len, 1);
	if (rez->num == NULL)
	{
		return 2;
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
 			//printf("eez minuz [%llu] = %d\n", j, rez->num[j-1]);
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
	if (b.len == 0)
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
		rem->num = malloc(rem->len);
		memcpy(rem->num, a.num, a.len);
		
		return 0;
	}
	
	if (verylongA_IS_A_POWER_OF_10(b))
	{
		rem->len = b.len - 1;
		rem->num = malloc(rem->len);
		quot->isNegativeBool = rem->isNegativeBool = a.isNegativeBool;
		
		quot->len = a.len - b.len + 1;
		quot->num = malloc(quot->len);
		memcpy(quot->num, a.num, quot->len);
		
		return 0;
	}
	
	quot->isNegativeBool = (a.isNegativeBool || b.isNegativeBool) && !(a.isNegativeBool && b.isNegativeBool) ? 1 : 0;
	quot->len = a.len - b.len + 1;
	quot->num = calloc(quot->len, 1);
	
	rem->len = 0;
	rem->num = NULL;
	
	unsigned long long i;
	verylong compare;
	char doDouble, aNeg = a.isNegativeBool, bNeg = b.isNegativeBool;
	a.isNegativeBool = b.isNegativeBool = 0;
	for (i = 0; i<quot->len; i++)
	{
		freeStruct(&compare);
		quot->num[i] = 5;
		doDouble = 1;
		if (longMul(b, *quot, &compare))
		{
			return 1;
		}
		while (1)
		{
			if (verylongA_EQUALS_verylongB_Bool(a, compare))
			{
				freeStruct(&compare);
				return 0;
			}
			else if (verylongA_IS_LESS_THAN_verylongB_Bool(compare, a))	//reikia didinti
			{
				if (quot->num[i]==1 || quot->num[i]==2 || quot->num[i]==4 || quot->num[i]==6 || quot->num[i]==9)
				{
					break;
				}
				quot->num[i] += doDouble ? 2 : 1;
				doDouble = 0;
				if (longMul(b, *quot, &compare))
				{
					freeStruct(&compare);
					return 1;
				}
			}
			else if (verylongA_IS_GREATER_THAN_verylongB_Bool(compare, a))		//reikia mazinti
			{
				if (quot->num[i]==1 || quot->num[i]==4 || quot->num[i]==6 || quot->num[i]==8 || quot->num[i]==9)
				{
					--quot->num[i];
					break;
				}
				quot->num[i] -= doDouble ? 2 : 1;
				doDouble = 0;
				if (longMul(b, *quot, &compare))
				{
					freeStruct(&compare);
					return 1;
				}
			}
		}
	}
	
	a.isNegativeBool = aNeg;
	b.isNegativeBool = bNeg;
	if (removeLeadingZeros(quot))
	{
		freeStruct(&compare);
		return 1;
	}
	if (longMul(b, *quot, &compare))
	{
		freeStruct(&compare);
		return 1;
	}
	compare.isNegativeBool = compare.isNegativeBool ? 0 : 1;
	if (longSum(a, compare, rem))
	{
		freeStruct(&compare);
		return 1;
	}
	freeStruct(&compare);
	
	return 0;
}
int longExp(verylong a, verylong b, verylong *exp)
{
	if (a.len == 0)
	{
		exp->isNegativeBool = 0;
		exp->len = 0;
		exp->num = NULL;
		return 0;
	}
	if (b.len == 0)
	{
		exp->isNegativeBool = 0;
		exp->len = 1;
		exp->num = malloc(1);
		if (exp->num == NULL)
		{
			return -1;
		}
		exp->num[0] = 1;
		return 0;
	}
	if (b.isNegativeBool == 1)
	{
		return -1;
	}
	exp->isNegativeBool = a.isNegativeBool ? b.num[b.len-1] % 2 == 1 ? 1 : 0 : 0;	//jei baze yra neigiama ir laipsnis nelyginis tai exponentas neigiamas
	if (verylongA_IS_A_POWER_OF_10(a))
	{
		if (a.len == 1)
		{
			exp->isNegativeBool = 0;
			exp->len = 1;
			exp->num = malloc(1);
			if (exp->num == NULL)
			{
				return -1;
			}
			exp->num[0] = 1;
			return 0;
		}
		verylong testlimit;
		if (castULongLongToVerylong(a.len - 1, &testlimit))
		{
			freeStruct(&testlimit);
			return -1;
		}
		if (longMul(testlimit, b, &testlimit))
		{
			freeStruct(&testlimit);
			return -1;
		}
		if (castVerylongToULongLong(testlimit, &(exp->len)))
		{
			freeStruct(&testlimit);
			return 1;	//exponent is over limit
		}
		freeStruct(&testlimit);
		++exp->len;
		exp->num = malloc(exp->len);
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
			exp->num = malloc(exp->len);
			if (exp->num == NULL)
			{
				return -1;
			}
			memcpy(exp->num, a.num, exp->len);
			return 0;
		}
		if (b.num[0] == 2)
		{
			longMul(a, a, exp);
			return 0;
		}
		if (b.num[0] == 3)
		{
			longMul(a, a, exp);
			longMul(*exp, a, exp);
			return 0;
		}
	}
	
	unsigned long long bInLLU;
	if (castVerylongToULongLong(b, &bInLLU))
	{
		return 1;
	}
	exp->len = 1;
	exp->num = malloc(1);	//paruosiamas exponentas nes rekursyviai is jo tik daugina ir jei nebutu inicijuota i 1 tai daygybos rezultatai butu keisti
	if (exp->num == NULL)
	{
		return -1;
	}
	exp->num[0] = 1;
	
	printf("\n");
	if (recursivePowerOfTwoExponent(&a, bInLLU, bInLLU, exp))
	{
		return 1;
	}
	return 0;
}
int recursivePowerOfTwoExponent(verylong *a, unsigned long long b, unsigned long long lastFound, verylong *exp)
{
	if (lastFound == 2)
	{
		if (b == 1)
		{
			if (longMul(*a, *exp, exp))
			{
				return 1;
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
	if (recursivePowerOfTwoExponent(a, closestPowerOf2 <= b ? b - closestPowerOf2 : b, closestPowerOf2, exp))
	{
		return 1;
	}
	if (longMul(*a, *a, a))		//a laikomas kiekvienas a pakeltas dvejeto laipsniu (a^1, a^2, a^4, a^8, ...)
	{
		return 1;
	}
	if (closestPowerOf2 <= b)		//jei padauginus is a pakelto dvejeto laipsniu exponentas nebus didesnis, jei norima, tada dauginti
	{
		if (longMul(*a, *exp, exp))
		{
			return 1;
		}
	}
	return 0;
}
//}

//{ other
int removeLeadingZeros(verylong *a)
{
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
	unsigned long long i;
	if(a.isNegativeBool)
		printf("-");
	for(i=0;i<a.len;i++)
		printf("%x", a.num[i]);
	printf("\n");
	
	return 0;
}
int castVerylongToULongLong(verylong a, unsigned long long *regular)
{
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
		a->len = 0;
		a->num = NULL;
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
	a->num = malloc(a->len);
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
