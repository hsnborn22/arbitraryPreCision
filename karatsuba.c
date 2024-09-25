#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "bigInt.h"

bigInt * splitLow(bigInt * num, int index) {
    if (index >= num->digitCount) {
        return num;
    } else {
        bigInt * output = malloc(sizeof(struct BIG_INT_STRUCT));
        int signFlag = (num->sign == -1) ? 1 : 0;
        output->sign = num->sign; 
        output->digitCount = index;
        output->digits = malloc(sizeof(int) * index);
        int start = num->digitCount - index;
        // fill the digits array of the output
        for (int i = start; i < num->digitCount; i++) {
            output->digits[i - start] = num->digits[i];
        }
        output->representation = getDigitStringFrom(output->digits, output->digitCount, num->sign); 
        return output;
    }
}

bigInt * splitHigh(bigInt * num, int index) {
    bigInt * output = malloc(sizeof(struct BIG_INT_STRUCT));
    if (index >= num->digitCount) {
        // if the index passed as an input is greater than the number of digits of the number, return 0.
        output->digitCount = 1;
        output->sign = 0;
        output->digits = calloc(1,sizeof(int));
        char * strRepr = malloc(sizeof(char)*2);
        strRepr[0] = '0';
        strRepr[1] = '\0';
        output->representation = strRepr;
        return output;
    } else {
        int signFlag = (num->sign == -1) ? 1 : 0;
        output->sign = num->sign; 
        output->digitCount = num->digitCount - index;
        output->digits = malloc(sizeof(int) * output->digitCount);
        // fill the digits array of the output
        for (int i = 0; i < output->digitCount; i++) {
            output->digits[i] = num->digits[i];
        }
        output->representation = getDigitStringFrom(output->digits, output->digitCount, num->sign); 
        return output;
    }
}

bigInt * karatsuba(bigInt * num1, bigInt * num2) {
    if (num1->digitCount == 1 || num2->digitCount == 1) {
        bigInt * output = naiveMultiplication(num1, num2);
        return output;
    }
    int m = max(num1, num2); 
    int m2 = m / 2;

    bigInt * high1 = splitHigh(num1, m2);
    bigInt * low1 = splitLow(num1, m2);
    bigInt * high2 = splitHigh(num2, m2);
    bigInt * low2 = splitLow(num2, m2);

    bigInt * z0 = karatsuba(low1,low2);
    bigInt * z2 = karasuba(high1,high2);
    bigInt * tempZ1a = sumBigInts(low1,high1); 
    bigInt * tempZ1b = sumBigInts(low2,high2);
    bigInt * z1 = karatsuba(tempZ1a, tempZ1b);
    
    bigInt * midTermTemp = subBigInts(z1, z2);
    bigInt * midTerm = subBigInts(midTermTemp, z0); 
    
    bigInt * outputTemp0 = bigIntShiftLeftDecimal(midTerm, m2);
    bigInt * outputTemp1 = bigIntShiftLeftDecimal(z2, m2 * 2);
    bigInt * outputTemp2 = sumBigInts(outputTemp0, outputTemp1);
    bigInt * output = sumBigInts(outputTemp2, z0);
    return output; 
}

int main(void) {
    bigInt num1 = initBigInt("100");
    bigInt num2 = initBigInt("201");
    bigInt * num3 = karatsuba(&num1, &num2);

    free(num1->representation);
    free(num1->digits);
    free(num2->representation);
    free(num2->digits);

    free(num3->representation);
    free(num3->digits);
    free(num3);
    return 0;    
}
