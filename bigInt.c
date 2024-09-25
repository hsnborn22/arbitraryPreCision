// Include the dependencies we will need for this library.
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

bigInt * sumBigInts(bigInt * int1, bigInt * int2);
bigInt * subBigInts(bigInt * int1, bigInt * int2);

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

/* ====================== initBigInt Function ============================= 

This function initializes a bigInt object: the input is the string we want
to use to initialize the object.
e.g. initBigInt("56") will initialize the bigInt with the following fields:
digits = [5,6] 
representation = "56"
sign = 1
digitCount = 2

========================================================================== */

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

/* ==================== negateBigInt Function ============================= 

-INPUT: The bigInt we want to negate; the input is of type bigInt* 
-OUTPUT: The negation of the input, i.e. - input.

========================================================================== */

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

/* ==================== reverseNumberArray Function ============================= 

-INPUT: The array we want to reverse (int *) and its length (int). 
-OUTPUT: The array reversed.

================================================================================= */

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

/* ==================== copyBigInt Function ============================= 

-INPUT: The bigInt we want to copy; the input is of type bigInt* 
-OUTPUT: A copy of the input

========================================================================== */

bigInt * copyBigInt(bigInt * numToCopy) {
    bigInt * result = malloc(sizeof(struct BIG_INT_STRUCT));
    int isNegative = (numToCopy->sign  == -1);
    result->digitCount = numToCopy->digitCount; 
    result->sign = numToCopy->sign; 
    result->representation = malloc(sizeof(char)*(numToCopy->digitCount + isNegative+1));
    strcpy(result->representation, numToCopy->representation);
    result->digits = malloc(sizeof(int) * (numToCopy->digitCount));
    memcpy(result->digits, numToCopy->digits, sizeof(int)*(numToCopy->digitCount));
    return result;
}

/* ==================== copyBigIntTo Procedure ============================= 

-INPUTS: The first input is the destination location, whereas the second 
destination is the source; the type of both inputs is bigInt *.
Effect: The procedure copies the source bigInt into the destination.

=========================================================================== */

void copyBigIntTo(bigInt * destination, bigInt * numToCopy) {
    int isNegative = (numToCopy->sign  == -1); // this flag yields 1 if the number to copy is negative and 0 if the number to copy is positive.
    destination->digitCount = numToCopy->digitCount; // copy the digitCount entry
    destination->sign = numToCopy->sign; // copy the sign
    destination->representation = malloc(sizeof(char)*(numToCopy->digitCount + isNegative+1)); // allocate space for the string representation of our number 
    strcpy(destination->representation, numToCopy->representation); // copy the representation
    destination->digits = malloc(sizeof(int) * (numToCopy->digitCount)); // allocate space for the digit array
    memcpy(destination->digits, numToCopy->digits, sizeof(int)*(numToCopy->digitCount)); // copy the digit array.
}

/* ==================== deallocateBigInt Procedure ============================= 

-INPUT: BigInt we want to deallocate.
Effect: The procedure deallocates the bigInt we passed as an input.

================================================================================ */

void deallocateBigInt(bigInt * number) {
    free(number->digits);
    free(number->representation);
    free(number);
}

/* ==================== deallocateBigIntFields Procedure ============================= 

-INPUT: BigInt whose fields we want to deallocate.
Effect: The procedure deallocates the fields containing the string representation and
int digit array of the bigInt, without deallocating the bigInt pointer itself.

===================================================================================== */

void deallocateBigIntFields(bigInt * number) {
    free(number->digits);
    free(number->representation);
}

// The behaviour of the following three functions is rather straightforward; they will
// return 1 if the bigInt we pass as an output is, respectively, positive, negative or 0
// and return 0 otherwise.

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

/* ==================== bigIntCmp Function ============================= 

-INPUTS: The function has two inputs of type bigInt * (bigInt pointer),
int1 and int2. These two inputs are the two bigInts we want to compare.
-OUTPUT: The function has one output (an int). The function will return 
0 if the two inputs are equal (i.e. int1 == int2), 1 if int1 > int2 and
-1 if int1 < int2. The output convention is very similar to the C strcmp function.

======================================================================= */

int bigIntCmp(bigInt * int1, bigInt * int2) { 
    // initialize the compare flag we will return to 0.
    int cmpFlag = 0;
    if (int1->digitCount > int2->digitCount) {
        cmpFlag = 1;
    } else if (int1->digitCount == int2->digitCount) {
        for (int i = 0; i < int1->digitCount; i++) {
            if (int1->digits[i] > int2->digits[i]) {
                cmpFlag = 1;
                break;
            } else if (int1->digits[i] < int2->digits[i]) {
                cmpFlag = -1;
                break;
            }
        }
    } else if (int1->digitCount < int2->digitCount) {
        cmpFlag = -1;
    }
    return cmpFlag;
}

/* ==================== bigIntIsLessThan Function ============================= 

-INPUTS: The function has two inputs of type bigInt * (bigInt pointer),int1 and
int2. These two inputs are the two bigInts we want to compare.
-OUTPUT: The function has one output (an int), to be interpreted as a boolean value.
It will return 1 if int1 < int2, and it will return 0 if int1 >= int2.

============================================================================== */

int bigIntIsLessThan(bigInt* int1, bigInt * int2) {
    return (bigIntCmp(int1,int2) == -1) ? 1:0;
}

/* ==================== bigIntIsGreaterThan Function ============================= 

-INPUTS: The function has two inputs of type bigInt * (bigInt pointer),int1 and
int2. These two inputs are the two bigInts we want to compare.
-OUTPUT: The function has one output (an int), to be interpreted as a boolean value.
It will return 1 if int1 > int2, and it will return 0 in all other cases.

============================================================================== */

int bigIntIsGreaterThan(bigInt* int1, bigInt * int2) {
    return (bigIntCmp(int1,int2) == 1) ? 1:0;
}

/* ==================== bigIntIsEqual Function ============================= 

-INPUTS: The function has two inputs of type bigInt * (bigInt pointer),int1 and
int2. These two inputs are the two bigInts we want to compare.
-OUTPUT: The function has one output (an int), to be interpreted as a boolean value.
It will return 0 if int1 != int2, and it will return 1 if int1 == int2.

============================================================================== */

int bigIntIsEqual(bigInt* int1, bigInt * int2) {
    return (bigIntCmp(int1,int2) == 0) ? 1:0;
}

bigInt * subBigInts(bigInt * int1, bigInt * int2) {
    bigInt * output = calloc(1,sizeof(struct BIG_INT_STRUCT));
    // case #1: both numbers are positive.
    if (int1->sign == 1 && int2->sign == 1) {
        // We are going to write the logic only for the case in which int1 is greater than int2, and cover all other cases using this case only.
        // if int1 > int2
        if (bigIntIsGreaterThan(int1, int2)) {
            output->sign = 1; // if a > b, a-b > 0
            int * digitCopy1 = calloc(sizeof(int1->digitCount), sizeof(int));
            int * digitCopy2 = calloc(sizeof(int2->digitCount), sizeof(int));
            // we copy the digit arrays of int1 and int2 into digitCopy1 and digitCopy2 and then reverse them.
            memcpy(digitCopy1, int1->digits, int1->digitCount * sizeof(int));
            memcpy(digitCopy2, int2->digits, int2->digitCount * sizeof(int));
            reverseArray(digitCopy1, int1->digitCount);
            reverseArray(digitCopy2, int2->digitCount);
            // allocate space for the output digit array
            int * outputDigitArray = calloc(1, sizeof(int) * int1->digitCount); // we make it hold maxLength integers: there are some cases in which it might be maxlength+1 long but we'll hand it manually with realloc if it occurs.
          
            int carry = 0;
            for (int i = 0; i < int1->digitCount; i++) {
                int sum = 0;
                if (i < int2->digitCount) {
                    sum = digitCopy1[i] - digitCopy2[i] + carry;
                } else {
                    sum = digitCopy1[i] + carry;
                }
                if (sum < 0) {
                    outputDigitArray[i] = sum + 10;
                    carry = -1;
                } else {
                    outputDigitArray[i] = sum;
                    carry = 0;
                } 
            }
            output->digitCount = int1->digitCount;
            reverseArray(outputDigitArray, output->digitCount);
            // now we have the result, with the addition of some unnecessary zeros; e.g. 2001 - 1799 = 0202 and digitcount=4, but we want just 202 and digitCount = 3
            // let's remove them  
            int * newOutput = removeUnnecessaryZeros(outputDigitArray, output->digitCount);
            int zerosBefore = calculateUselessZeros(outputDigitArray, output->digitCount);
            output->digitCount -= zerosBefore;
            free(outputDigitArray);
            free(digitCopy1);
            free(digitCopy2);
            output->digits = newOutput;
            char * repr = getDigitStringFrom(newOutput, output->digitCount, 1);
            output->representation = repr;
            
        } else if (bigIntIsEqual(int1,int2)) {
            // sub-case #2: if the two numbers are equal, return 0
            int * fDig = calloc(1,sizeof(int)); // array of size one that will store the digits of output ([0]). By callocing it we already init it to 0 so we dont need to modify its values.
            fDig[0] = 0;
            char * fStr = malloc(sizeof(char)*2); // the string representation of our output; it will be comprised of only two chars, the 0 value and the null terminator (\0).
            fStr[0] = '0';
            fStr[1] = '\0';
            output->sign = 0; // set the sign to 0
            output->digitCount = 1; // set the digit count to 1.
            output->digits = fDig; 
            output->representation = fStr;
        } else if (bigIntIsLessThan(int1,int2)) {
            // sub-case #3: if int1 < int2, we return - (int2 - int1) and compute int2-int1 with the sub-case #1 logic.
            bigInt * temp = subBigInts(int2,int1); 
            char * tempRepr = getDigitStringFrom(temp->digits, temp->digitCount, -1);
            output->representation = tempRepr;
            output->digits = malloc(sizeof(int) * temp->digitCount);
            memcpy(output->digits, temp->digits, sizeof(int) * temp->digitCount);
            output->sign = -1;
            output->digitCount = temp->digitCount;
            deallocateBigInt(temp);
        }
    } else if (int1->sign == -1 && int2->sign == -1) {
        // case #2: both numbers are negative.
        // (-a) - (-b) = b -a, so we just compute b-a and use case#1 logic.
        bigInt * temp = subBigInts(int2,int1);
        copyBigIntTo(output, temp);
        deallocateBigInt(temp);
    } else if (int1->sign == 1 && int2->sign == -1) {
        // case #3: int1 > 0 and int2 < 0
        // i.e. b = -|b| and a = |a|
        // |a| - (-|b|) = |a| + |b|; we compute the sum of the abs values.
        int2->sign = 1; // temporarily switch the sign of int2.
        bigInt * temp = sumBigInts(int1, int2);
        copyBigIntTo(output, temp);
        deallocateBigInt(temp);
        int2->sign = -1;
    } else if (int1->sign == -1 && int2->sign == 1) {
        // case #4: int1 < 0 and int2 > 0
        // We compute -|a| + (-|b|) with sumBigInts
        int2->sign = -1; // as in the case before, temporairily set sign to be -1
        bigInt * temp = sumBigInts(int1,int2); // compute the sum of the two negative values.
        copyBigIntTo(output, temp);
        output->sign = -1;
        deallocateBigInt(temp);
        int2->sign = 1;
    } else if (int1->sign == 0) {
        copyBigIntTo(output, int2);
    } else if (int2->sign == 0) {
        copyBigIntTo(output, int1);
    }
    return output;
}

bigInt * sumBigInts(bigInt * int1, bigInt * int2) {
    bigInt * output = calloc(1,sizeof(struct BIG_INT_STRUCT));
    if (int1->sign == 1 && int2->sign == 1) {
        output->sign = 1; // a sum of positive numbers is positive
        int * digitCopy1 = calloc(int1->digitCount, sizeof(int));
        int * digitCopy2 = calloc(int2->digitCount, sizeof(int));
        // We loop starting from the first non-zero value up to the end of the array and save the values in output.        int * digitCopy2 = calloc(int2->digitCount, sizeof(int));
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
        free(digitCopy1);
        free(digitCopy2);
        char * repr = getDigitStringFrom(outputDigitArray, output->digitCount, 1);
        output->representation = repr;
    } else if (int1->sign == 0) {
        copyBigIntTo(output, int2);
    } else if (int2->sign == 0) {
        copyBigIntTo(output, int1);
    } else if (int1->sign == -1 && int2->sign == -1) {
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
    } else if (int1->sign == -1 && int2->sign == 1) {
        // if int1 < 0 and int2 > 0, we compute int2 - int1
        int1->sign = 1; // temp.set int1 sign to be 1.
        bigInt * temp = subBigInts(int2,int1); // compute the sub of the two values. (int2 - int1)
        copyBigIntTo(output, temp);
        deallocateBigInt(temp);
        int1->sign = -1;
    } else if (int1->sign == 1 && int2->sign == -1) {
        // the case is totally analogous as the one above:
        int2->sign = 1; // as in the case before, temp. set sign to be 1
        bigInt * temp = subBigInts(int1,int2); // compute int1 - int2.
        copyBigIntTo(output, temp);
        deallocateBigInt(temp);
        int2->sign = -1;
    }
    return output;
}

/* ==================== naiveMultiplication Function ============================= 

-INPUTS: The function has two inputs of type bigInt * (bigInt pointer),int1 and
int2. These two inputs are the two bigInts we want to multiply.
-OUTPUT: The product of the two inputs, int1 * int2. 

============================================================================== */

bigInt * naiveMultiplication(bigInt * int1, bigInt * int2) {
    bigInt * output = calloc(1,sizeof(struct BIG_INT_STRUCT));
    
    int * digitCopy1 = calloc(int1->digitCount, sizeof(int));
    int * digitCopy2 = calloc(int2->digitCount, sizeof(int));
    // we copy the digit arrays of int1 and int2 into digitCopy1 and digitCopy2 and thenn reverse them , so that we get least significant values first
    memcpy(digitCopy1, int1->digits, int1->digitCount * sizeof(int));
    memcpy(digitCopy2, int2->digits, int2->digitCount * sizeof(int));
    reverseArray(digitCopy1, int1->digitCount);
    reverseArray(digitCopy2, int2->digitCount);
    
    // we loop over the digits of int2 and allocate space for an array of bigInts
    bigInt ** partialProductsArray = malloc(sizeof(struct BIG_INT_STRUCT*) * int2->digitCount);
    for (int i = 0; i < int2->digitCount; i++) {
        // for each digit of int2, we create a partial product; we will sum all the partial products at the end
        bigInt * currentPartialProduct = calloc(1,sizeof(struct BIG_INT_STRUCT));
        currentPartialProduct->sign = 1;
        currentPartialProduct->digitCount = int1->digitCount;
        int * currppDigits = calloc(int1->digitCount, sizeof(int));
        int carry = 0;
        for (int j = 0; j < int1->digitCount; j++) {
            int p = (digitCopy1[j] * digitCopy2[i]) + carry; 
            carry = p / 10; 
            currppDigits[j] = p % 10;
        }
        if (carry != 0) {
            // if the last carry is not 0, we set the last digit to be said carry (i.e. 9 x 999 , the last carry is 8 and in fact 9x999=8991
            currentPartialProduct->digitCount ++;
            currppDigits = realloc(currppDigits, sizeof(int) * (int1->digitCount + 1));
            currppDigits[int1->digitCount] = carry;
        }
        
        // we reverse the array back to make it match the standard used in bigNum data structure.
        reverseArray(currppDigits, currentPartialProduct->digitCount);
        // we now shift the result of the previous step i number of times to the left
        decimalLeftShiftArray(&currppDigits, currentPartialProduct->digitCount, i);
        currentPartialProduct->digitCount += i; // take into account the zeros we added in counting the numbers of digits 
        currentPartialProduct->digits = currppDigits;
        char * tempRepr = getDigitStringFrom(currppDigits, currentPartialProduct->digitCount, 1);
        currentPartialProduct->representation = tempRepr;
        partialProductsArray[i] = currentPartialProduct;
    }
    int * zeroDig = calloc(1,sizeof(int));
    char * zeroStr = malloc(2*sizeof(char));
    zeroStr[0] = '0';
    zeroStr[1] = '\0';
    output->sign = 0;
    output->digitCount = 1;
    output->representation = zeroStr;
    output->digits = zeroDig;
    // looping over partialProductsArray and summing all of them
    for (int i = 0; i < int2->digitCount; i++) {
        bigInt * tempSums = sumBigInts(output, partialProductsArray[i]);
        deallocateBigIntFields(output);
        copyBigIntTo(output, tempSums);
        deallocateBigInt(tempSums);
    }
    
    for (int i = 0; i < int2->digitCount; i++) {
        deallocateBigInt(partialProductsArray[i]);
    }
    free(partialProductsArray);
    output->sign = int1->sign * int2-> sign; // the sign of the output is the product of the signs.
    free(digitCopy1);
    free(digitCopy2);
    return output;
}

int main(void) {
    return 0;
}
