#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Initialize and declare the array of digits in form of chars
// that we will use throughout the program.
char acceptableDigits[] = {'0','1','2','3','4','5','6','7','8','9'};

// bigInt type: this is the type that will represent a bigInt

typedef struct BIG_INT_STRUCT {
    int * digits; // This is the array of digits.
    char * representation; // this is the string representation of the bigInt
    int sign; // this is going to be equal to 1 if it's positive, -1 if it's negative and 0 if it's 0.
    int digitCount;  // this is the number of digits of the number.
} bigInt; 

char * getDigitStringFrom(int * digits, int digitLength, int sign) {
    // save a flag that indicates if the number is negative in isNegative.
    int isNegative = (sign  == -1);
    // allocate the space for the output string via calloc (i.e. allocate and initialize space with 0)
    char * outputString = calloc(1, sizeof(char) * (digitLength + isNegative + 1)); // +1 for '\0' null terminator.
    
    if (outputString == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    
    // initialize stringLength to 0 if the value is positive and does not need any - in front
    int stringLength = 0;
    if (isNegative) {
        // if its negative add oen extra char for the -
        outputString[0] = '-';
        stringLength = 1;
    }

    for (int i = 0; i < digitLength; i++) {
        outputString[i + stringLength] = (char)(digits[i] + 48);
    }
    outputString[digitLength + stringLength] = '\0';

    return outputString;
}

// initBigInt method to initialize a bigInt object
bigInt initBigInt(char * initString) {
    bigInt output;
    int i = 0;
    int signEncounteredCounter = 0;
    int digitCount = 0; 
    int * digits = calloc(1, sizeof(int));

    while (initString[i] == ' ') {
        i++;
    }

    while (initString[i] != '\0') {
        if (initString[i] == '-' && signEncounteredCounter == 0) {
            signEncounteredCounter++;
            i++;
        } else if (initString[i] == '-' && signEncounteredCounter != 0) {
            break;  
        } else if (binarySearch(acceptableDigits, 0, 10, initString[i]) != -1) {
            digitCount++;
            digits = realloc(digits, sizeof(int) * digitCount);
            digits[digitCount - 1] = (int)initString[i] - 48;
            i++;
        } else {
            break; 
        }
    }

    int j = 0; 
    while (digits[j] == 0) {
        if (j == digitCount - 1 || digitCount == 0) {
            int zeroArr[] = {0};
            output.digits = malloc(sizeof(int));
            if (output.digits == NULL) {
                exit(0);
            }
            memcpy(output.digits, zeroArr, sizeof(int));
            output.digitCount = 1;
            output.representation = malloc(sizeof(char)*2);
            if (output.representation == NULL) {
            // Handle memory allocation failure
            free(output.digits);
            }
            strcpy(output.representation, "0");
            output.sign = 0;
            return output;
        } else {
            j++;
        }
    }
    int * actualDigits = cutArray(digits, digitCount, j);
    free(digits);
    if (actualDigits == NULL) {
        // Handle error, e.g., set an error flag in output, return a special error value, etc.
        return output; // Or use another method to signal an error
    }
    int actualDigitCount = digitCount - j;


    char * actualString = getDigitStringFrom(actualDigits, actualDigitCount, signEncounteredCounter);
    if (actualString == NULL) {
        // Handle error similarly
        free(actualDigits); // Free memory allocated by cutArray
        return output;      // Return the struct signaling an error
    }
    output.representation = actualString; 
    output.digits = actualDigits; 
    output.digitCount = actualDigitCount; 
    output.sign = signEncounteredCounter ? -1 : 1; 
    return output; 
}

// negateBigInt function: this function changes the sign of a bigInt
bigInt * negateBigInt(bigInt * bVar) {
    // Declare the bigInt variable we're going to return
    bigInt * output = malloc(sizeof(struct BIG_INT_STRUCT)); 
    // check if the bigInt we want to negate is positive or negative via ternary operator
    // isPositive is 1 if the bigInt bVar is positive and 0 if it's negative
    int isPositive = (bVar->sign == 1) ? 1 : 0;
    // Create a buffer (array of chars) of length bVar.digitCount + isPositive
    // This is because if the bigInt we want to negate is positive, then the string representation will have one more character
    // , namely the - character in front. 
    char * buffer = malloc((bVar->digitCount + isPositive + 1)*sizeof(char));
    // We're going to apply different logic
    if (bVar->sign == -1) {
        // if our original bigInt is negative, we're going to copy everything inside of the string representation except the first character (the minus).
        for (int i = 0; i < bVar->digitCount; i++) {
            buffer[i] = bVar->representation[i+1];
        }
    } else {
        sprintf(buffer, "-%s", bVar->representation);
    }
    buffer[bVar->digitCount + isPositive] = '\0';
    output->sign = - bVar->sign;
    output->digits = malloc(bVar->digitCount*sizeof(int));
    memcpy(output->digits, bVar->digits, bVar->digitCount * sizeof(int));
    output->representation = buffer;
    output->digitCount = bVar->digitCount;

    return output;     
}

int * reverseNumberArray(int * array, int length) {
    int * result = malloc(sizeof(int) * length);
    if (result == NULL) {
        return NULL;
    }
    for (int i = 1; i <= length; i++) {
        result[length - i] = array[i - 1];
    }
    return result;
}

bigInt * copyBigInt(bigInt * numToCopy) {
    bigInt * result = malloc(sizeof(struct BIG_INT_STRUCT));
    int isNegative = (numToCopy->sign  == -1);
    result->digitCount = numToCopy->digitCount; 
    result->sign = numToCopy->sign; 
    result->representation = malloc(sizeof(char)*(numToCopy->digitCount + isNegative+1));
    strcpy(result->representation, numToCopy->representation);
    result->digits = malloc(sizeof(int) * (numToCopy->digitCount));
    memcpy(result->digits, numToCopy->digits, sizeof(char)*(numToCopy->digitCount + isNegative + 1));
    return result;
}

int isBigIntPositive(bigInt bVar) {
    int returnValue = (bVar.sign == 1) ? 1 : 0;
    return returnValue; 
}

int isBigIntNegative(bigInt bVar) {
    int returnValue = (bVar.sign == -1) ? 1 : 0;
    return returnValue; 
}

int isBigIntZero(bigInt bVar) {
    int returnValue = (bVar.sign == 0) ? 1 : 0;
    return returnValue; 
}

bigInt * sumBigInts(bigInt * int1, bigInt * int2) {
    bigInt * output = calloc(1,sizeof(struct BIG_INT_STRUCT));
    if (int1->sign == 1 && int2->sign == 1) {
        output->sign = 1; // a sum of positive numbers is positive
        int * digitCopy1 = calloc(int1->digitCount, sizeof(int));
        int * digitCopy2 = calloc(int2->digitCount, sizeof(int));
        // we copy the digit arrays of int1 and int2 into digitCopy1 and digitCopy2 and thenn reverse them , so that we get least significant values first
        memcpy(digitCopy1, int1->digits, int1->digitCount * sizeof(int));
        memcpy(digitCopy2, int2->digits, int2->digitCount * sizeof(int));
        reverseArray(digitCopy1, int1->digitCount);
        reverseArray(digitCopy2, int2->digitCount);
        int maxLength = (int1->digitCount > int2->digitCount) ? int1->digitCount : int2->digitCount;
        // allocate space for the output digit array
        int * outputDigitArray = calloc(1, sizeof(int) * maxLength); // we make it hold maxLength integers: there are some cases in which it might be maxlength+1 long but we'll hand it manually with realloc if it occurs.
        int minLength = (int1->digitCount < int2->digitCount) ? int1->digitCount : int2->digitCount;
        
        // do the loop to add the numbers. We loop from i = 0 to i = minLength
        int carry = 0;
        for (int i = 0; i < maxLength; i++) {
          int sum = 0;
          if (i < int1->digitCount && i < int2->digitCount) {
              sum = digitCopy1[i] + digitCopy2[i] + carry;
          } else if (i < int1->digitCount && i >= int2->digitCount) {
              sum = digitCopy1[i] + carry;
          } else if (i < int2->digitCount && i >= int1->digitCount) {
              sum = digitCopy2[i] + carry;
          }
          
          outputDigitArray[i] = sum % 10;
          if (sum > 9) {
              carry = 1;
          } else {
            carry = 0;    
          }
        }
        output->digitCount = maxLength;
        // if carry is 1, then we will need an extra digit place.
        if (carry == 1) {
            outputDigitArray = realloc(outputDigitArray, sizeof(int) * (maxLength + 1));
            outputDigitArray[maxLength] = 1;
            output->digitCount ++;
        }
        reverseArray(outputDigitArray, output->digitCount);
        output->digits = outputDigitArray;
        char * repr = getDigitStringFrom(outputDigitArray, output->digitCount, 1);
        output->representation = repr;
    } else if (int1->sign == 0) {
        memcpy(output, int2, sizeof(struct BIG_INT_STRUCT));
    } else if (int2->sign == 0) {
        memcpy(output, int1, sizeof(struct BIG_INT_STRUCT));
    } else if (int1->sign == -1 && int2->sign == -2) {
        int1->sign = 1;
        int2->sign = 1;
        bigInt * temp = sumBigInts(int1, int2);
        int1->sign = -1;
        int2->sign = -1;
        output->sign = -1;
        output->digits = temp->digits;
        char * minusAddedString = addMinus(temp->representation, temp->digitCount);
        output->representation = minusAddedString;
        output->digitCount = temp->digitCount;
        free(temp);
        return output;
    }
    return output;
}

int main(void) {
    bigInt bigNum1 = initBigInt("0");
    bigInt bigNum2 = initBigInt("6");
    bigInt * bigNum3 = sumBigInts(&bigNum1, &bigNum2);

    printf(" Representation: %s\n", bigNum3->representation);
    free(bigNum1.representation);
    free(bigNum1.digits);
    free(bigNum2.digits);
    free(bigNum2.representation);
    return 0;
}
