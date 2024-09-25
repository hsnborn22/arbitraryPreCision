typedef struct BIG_INT_STRUCT {
    int * digits; // This is the array of digits.
    char * representation; // this is the string representation of the bigInt
    int sign; // this is going to be equal to 1 if it's positive, -1 if it's negative and 0 if it's 0.
    int digitCount;  // this is the number of digits of the number.
} bigInt; 

bigInt * sumBigInts(bigInt * int1, bigInt * int2);
bigInt * subBigInts(bigInt * int1, bigInt * int2);
bigInt * naiveMultiplication(bigInt *int1, bigInt * int2);

char * getDigitStringFrom(int * digits, int digitLength, int sign);
bigInt * bigIntShiftLeftDecimal(bigInt * number, int amount);

bigInt initBigInt(char * initString);
void deallocateBigInt(bigInt * number);
void deallocateBigIntFields(bigInt * number);
void copyBigIntTo(bigInt * destination, bigInt * numToCopy);
