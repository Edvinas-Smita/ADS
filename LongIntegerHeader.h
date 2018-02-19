typedef struct muchlong
{
	char *num;
	unsigned long long len;
	unsigned char isNegativeBool;
} verylong;

void freeStruct(verylong *a);
int readToStruct(FILE *input, verylong *a);

int longIsEqual(verylong a, verylong b);
int longIsGreater(verylong a, verylong b);
int longIsLess(verylong a, verylong b);

int longSum(verylong a, verylong b, verylong *sum);
int longMul(verylong a, verylong b, verylong *mul);
int longMul_karatsuba(verylong a, verylong b, verylong *rez);
int longDiv(verylong a, verylong b, verylong *quot, verylong *div);
int longExp(verylong a, verylong b, verylong *exp);
int left_shift(verylong *a, long long count);
int print_bcdh(verylong a);

