typedef struct muchlong
{
	char *num;
	unsigned long long len;
	unsigned char isNegativeBool;
} verylong;

int freeStruct(verylong *a);
int print_bcdh(verylong a);
int readToStruct(FILE *input, verylong *a);
int longSum(verylong a, verylong b, verylong *sum);
int longMul(verylong a, verylong b, verylong *mul);
