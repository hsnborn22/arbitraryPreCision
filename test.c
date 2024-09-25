#include <stdio.h>

int main(void) {
    int arr[] = {101, 222, 11, -5, 251, -3, 44, 1, 0, 0, 8, 7, 9867, 111, -122, 78999, 987, 111, -718, 661, 581, -11, 11, 11, 222, 901, -45, 23, -67, 89, -12, 34, -56, 78, -90, 12, -34, 56, -78, 90, -23, 45, -67, 89, -12, 34, -56, 78, -90, 12, -34, 56, -78, 90, -23, 45, -67, 89, -12, 34, -56, 78, -90, 12, -34, 56, -78, 90, -23, 45, -67, 89, -12, 34, -56, 78, -90, 12, -34, 56, -78, 90, -23, 45, -67, 89, -12, 34, -56, 78, -90, 12, -34, 56, -78, 90, -23, 45, -67, 89, -12, 34, -56, 78, -90, 12, -34, 56, -78, 90, -23, 45, -67, 89, -12, 34, -56, 78, -90, 12, -34, 56, -78, 90};
    int length = (int)(sizeof(arr) / sizeof(int));
    char ad[] = "%d";
    char as[] = "%s";
    for (int i = 0; i < length-2; i+= 2) {
        printf("printf(\"Subtraction between: %d and %d. Expected result: %d \"); \n", arr[i], arr[i+1], arr[i] - arr[i+1]);
        printf("bigNum1 = initBigInt(\"%d\");\nbigNum2 = initBigInt(\"%d\");\nbigNum3 = subBigInts(&bigNum1, &bigNum2); \nprintf(\" Representation: %s\\n Digit Count: %s \\n Sign: %s\\n\", bigNum3->representation, bigNum3->digitCount, bigNum3->sign); \nfor (int i = 0; i < bigNum3->digitCount; i++) {\n printf(\"%s \\n\", bigNum3->digits[i]);\n}\nfree(bigNum1.representation);\nfree(bigNum1.digits);\nfree(bigNum2.digits);\nfree(bigNum2.representation);\n", arr[i], arr[i+1], as,ad,ad,ad);
    }
    return 0;
}
