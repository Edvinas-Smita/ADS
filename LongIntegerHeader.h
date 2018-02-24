typedef struct muchlong
{
	char *num;
	unsigned long long len;
	unsigned char isNegativeBool;
} verylong;

//{
void freeStruct(verylong *a);
int readToStruct(FILE *input, verylong *a);


int verylongA_EQUALS_verylongB_Bool(verylong a, verylong b);
int verylongA_IS_GREATER_THAN_verylongB_Bool(verylong a, verylong b);
int verylongA_IS_LESS_THAN_verylongB_Bool(verylong a, verylong b);

int verylongA_EQUALS_longlongB_Bool(verylong a, long long b, int treatAsSignedBool);
int verylongA_IS_GREATER_THAN_longlongB_Bool(verylong a, long long b, int treatAsSignedBool);
int verylongA_IS_LESS_THAN_longlongB_Bool(verylong a, long long b, int treatAsSignedBool);

int verylongA_CAN_BE_STORED_IN_ULongLong(verylong a);
int verylongA_IS_A_POWER_OF_10_Bool(verylong a);


int longSum(verylong a, verylong b, verylong *sum);
int longMul(verylong a, verylong b, verylong *mul);
int longDiv(verylong a, verylong b, verylong *quot, verylong *rem);
int longExp(verylong a, verylong b, verylong *exp);
int recursivePowerOfTwoExponent(verylong *a, unsigned long long b, unsigned long long lastFound, verylong *exp);

int removeLeadingZeros(verylong *a);
int print_bcdh(verylong a);
int castVerylongToULongLong(verylong a, unsigned long long *regular);
int castULongLongToVerylong(unsigned long long regular, verylong *a);
//}
