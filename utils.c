#include <stdio.h>
#include <stdlib.h>
// binarySearch implemented for optimal searching for digits 
// passed in to the init method (we need to check if these chars are digits).

int binarySearch(char arr[], int l, int r, char x) {
    // checking if there are elements in the subarray
    if (r >= l) {
 
        // calculating mid point
        int mid = l + (r - l) / 2;
 
        // If the element is present at the middle itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then it can only
        // be present in left subarray
        if (arr[mid] > x) {
            return binarySearch(arr, l, mid - 1, x);
        }
 
        // Else the element can only be present in right
        // subarray
        return binarySearch(arr, mid + 1, r, x);
    }
 
    // We reach here when element is not present in array
    return -1;
}

// cutArray function: this function is responsible for taking an array and "cutting" everything
// from a digit onwards.

int * cutArray(int * array, int arrayLength,int index) {
    // allocate space for the output array
    int * output = malloc((arrayLength - index) * sizeof(int));
    // copy everything inside from the input array after index 
    for (int i = index; i < arrayLength; i++) {
        output[i - index] = array[i];
    }
    return output; 
}

// function to reverse an array of integers.
void reverseArray(int arr[], int size)
{
    for (int i = 0; i < size/2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

// function to add a minus char in front of a string
char * addMinus(char * string, int n) {
    char * output = malloc(sizeof(char) * (n+2));
    output[0] = '-';
    for (int i = 0; i < n; i++) {
        output[i] = string[i];
    }
    output[n+1] = '\0';
    return output;
}